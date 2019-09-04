#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct bnx2x_phy {int addr; } ;
struct bnx2x {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_CTRL ; 
 int /*<<< orphan*/  MDIO_PMA_REG_TX_DISABLE ; 
 int MISC_REGISTERS_GPIO_1 ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_OUTPUT_HIGH ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_OUTPUT_LOW ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 int NIG_MASK_MI_INT ; 
 int NIG_MASK_SERDES0_LINK_STATUS ; 
 int NIG_MASK_XGXS0_LINK10G ; 
 int NIG_MASK_XGXS0_LINK_STATUS ; 
 scalar_t__ NIG_REG_MASK_INTERRUPT_PORT0 ; 
 int /*<<< orphan*/  NIG_REG_PORT_SWAP ; 
 int /*<<< orphan*/  NIG_REG_STRAP_OVERRIDE ; 
 int PORT_0 ; 
 size_t PORT_1 ; 
 int PORT_MAX ; 
 scalar_t__ REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_8073_8727_external_rom_boot (struct bnx2x*,struct bnx2x_phy*,int) ; 
 int /*<<< orphan*/  bnx2x_bits_dis (struct bnx2x*,scalar_t__,int) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_get_ext_phy_reset_gpio (struct bnx2x*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bnx2x_populate_phy (struct bnx2x*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,struct bnx2x_phy*) ; 
 int /*<<< orphan*/  bnx2x_set_gpio (struct bnx2x*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bnx2x_8727_common_init_phy(struct bnx2x *bp,
				      u32 shmem_base_path[],
				      u32 shmem2_base_path[], u8 phy_index,
				      u32 chip_id)
{
	s8 port, reset_gpio;
	u32 swap_val, swap_override;
	struct bnx2x_phy phy[PORT_MAX];
	struct bnx2x_phy *phy_blk[PORT_MAX];
	s8 port_of_path;
	swap_val = REG_RD(bp, NIG_REG_PORT_SWAP);
	swap_override = REG_RD(bp, NIG_REG_STRAP_OVERRIDE);

	reset_gpio = MISC_REGISTERS_GPIO_1;
	port = 1;

	/* Retrieve the reset gpio/port which control the reset.
	 * Default is GPIO1, PORT1
	 */
	bnx2x_get_ext_phy_reset_gpio(bp, shmem_base_path[0],
				     (u8 *)&reset_gpio, (u8 *)&port);

	/* Calculate the port based on port swap */
	port ^= (swap_val && swap_override);

	/* Initiate PHY reset*/
	bnx2x_set_gpio(bp, reset_gpio, MISC_REGISTERS_GPIO_OUTPUT_LOW,
		       port);
	usleep_range(1000, 2000);
	bnx2x_set_gpio(bp, reset_gpio, MISC_REGISTERS_GPIO_OUTPUT_HIGH,
		       port);

	usleep_range(5000, 10000);

	/* PART1 - Reset both phys */
	for (port = PORT_MAX - 1; port >= PORT_0; port--) {
		u32 shmem_base, shmem2_base;

		/* In E2, same phy is using for port0 of the two paths */
		if (CHIP_IS_E1x(bp)) {
			shmem_base = shmem_base_path[0];
			shmem2_base = shmem2_base_path[0];
			port_of_path = port;
		} else {
			shmem_base = shmem_base_path[port];
			shmem2_base = shmem2_base_path[port];
			port_of_path = 0;
		}

		/* Extract the ext phy address for the port */
		if (bnx2x_populate_phy(bp, phy_index, shmem_base, shmem2_base,
				       port_of_path, &phy[port]) !=
				       0) {
			DP(NETIF_MSG_LINK, "populate phy failed\n");
			return -EINVAL;
		}
		/* disable attentions */
		bnx2x_bits_dis(bp, NIG_REG_MASK_INTERRUPT_PORT0 +
			       port_of_path*4,
			       (NIG_MASK_XGXS0_LINK_STATUS |
				NIG_MASK_XGXS0_LINK10G |
				NIG_MASK_SERDES0_LINK_STATUS |
				NIG_MASK_MI_INT));


		/* Reset the phy */
		bnx2x_cl45_write(bp, &phy[port],
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_CTRL, 1<<15);
	}

	/* Add delay of 150ms after reset */
	msleep(150);
	if (phy[PORT_0].addr & 0x1) {
		phy_blk[PORT_0] = &(phy[PORT_1]);
		phy_blk[PORT_1] = &(phy[PORT_0]);
	} else {
		phy_blk[PORT_0] = &(phy[PORT_0]);
		phy_blk[PORT_1] = &(phy[PORT_1]);
	}
	/* PART2 - Download firmware to both phys */
	for (port = PORT_MAX - 1; port >= PORT_0; port--) {
		if (CHIP_IS_E1x(bp))
			port_of_path = port;
		else
			port_of_path = 0;
		DP(NETIF_MSG_LINK, "Loading spirom for phy address 0x%x\n",
			   phy_blk[port]->addr);
		if (bnx2x_8073_8727_external_rom_boot(bp, phy_blk[port],
						      port_of_path))
			return -EINVAL;
		/* Disable PHY transmitter output */
		bnx2x_cl45_write(bp, phy_blk[port],
				 MDIO_PMA_DEVAD,
				 MDIO_PMA_REG_TX_DISABLE, 1);

	}
	return 0;
}