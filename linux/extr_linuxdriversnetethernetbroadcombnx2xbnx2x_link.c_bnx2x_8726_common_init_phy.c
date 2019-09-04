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
typedef  int u32 ;
struct bnx2x_phy {int dummy; } ;
struct bnx2x {int dummy; } ;
typedef  size_t s8 ;

/* Variables and functions */
 scalar_t__ CHIP_IS_E1x (struct bnx2x*) ; 
 int /*<<< orphan*/  DP (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDIO_PMA_DEVAD ; 
 int /*<<< orphan*/  MDIO_PMA_REG_GEN_CTRL ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_0 ; 
 int MISC_REGISTERS_GPIO_3 ; 
 int /*<<< orphan*/  MISC_REGISTERS_GPIO_HIGH ; 
 int MISC_REGISTERS_GPIO_PORT_SHIFT ; 
 int /*<<< orphan*/  MISC_REG_GPIO_EVENT_EN ; 
 int /*<<< orphan*/  NETIF_MSG_LINK ; 
 size_t PORT_MAX ; 
 int REG_RD (struct bnx2x*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_WR (struct bnx2x*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_cl45_write (struct bnx2x*,struct bnx2x_phy*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bnx2x_ext_phy_hw_reset (struct bnx2x*,int /*<<< orphan*/ ) ; 
 scalar_t__ bnx2x_populate_phy (struct bnx2x*,int /*<<< orphan*/ ,int,int,size_t,struct bnx2x_phy*) ; 
 int /*<<< orphan*/  bnx2x_set_gpio (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int bnx2x_8726_common_init_phy(struct bnx2x *bp,
				      u32 shmem_base_path[],
				      u32 shmem2_base_path[], u8 phy_index,
				      u32 chip_id)
{
	u32 val;
	s8 port;
	struct bnx2x_phy phy;
	/* Use port1 because of the static port-swap */
	/* Enable the module detection interrupt */
	val = REG_RD(bp, MISC_REG_GPIO_EVENT_EN);
	val |= ((1<<MISC_REGISTERS_GPIO_3)|
		(1<<(MISC_REGISTERS_GPIO_3 + MISC_REGISTERS_GPIO_PORT_SHIFT)));
	REG_WR(bp, MISC_REG_GPIO_EVENT_EN, val);

	bnx2x_ext_phy_hw_reset(bp, 0);
	usleep_range(5000, 10000);
	for (port = 0; port < PORT_MAX; port++) {
		u32 shmem_base, shmem2_base;

		/* In E2, same phy is using for port0 of the two paths */
		if (CHIP_IS_E1x(bp)) {
			shmem_base = shmem_base_path[0];
			shmem2_base = shmem2_base_path[0];
		} else {
			shmem_base = shmem_base_path[port];
			shmem2_base = shmem2_base_path[port];
		}
		/* Extract the ext phy address for the port */
		if (bnx2x_populate_phy(bp, phy_index, shmem_base, shmem2_base,
				       port, &phy) !=
		    0) {
			DP(NETIF_MSG_LINK, "populate phy failed\n");
			return -EINVAL;
		}

		/* Reset phy*/
		bnx2x_cl45_write(bp, &phy,
				 MDIO_PMA_DEVAD, MDIO_PMA_REG_GEN_CTRL, 0x0001);


		/* Set fault module detected LED on */
		bnx2x_set_gpio(bp, MISC_REGISTERS_GPIO_0,
			       MISC_REGISTERS_GPIO_HIGH,
			       port);
	}

	return 0;
}