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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;

/* Variables and functions */
 int CALDUTY ; 
 int PPMDRIFTMAX_HI ; 
 int RXCDRCALFOSC0 ; 
 int RXDPIF ; 
 int read_phy_reg (int /*<<< orphan*/ ,int,int) ; 
 int* sata_phy_config1 ; 
 int* sata_phy_config2 ; 
 int /*<<< orphan*/  write_phy_reg (int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void config_sata_phy(u64 regbase)
{
	u32 port, i, reg;
	u8 val;

	for (port = 0; port < 2; port++) {
		for (i = 0, reg = RXCDRCALFOSC0; reg <= CALDUTY; reg++, i++)
			write_phy_reg(regbase, reg, port, sata_phy_config1[i]);

		for (i = 0, reg = RXDPIF; reg <= PPMDRIFTMAX_HI; reg++, i++)
			write_phy_reg(regbase, reg, port, sata_phy_config2[i]);

		/* Fix for PHY link up failures at lower temperatures */
		write_phy_reg(regbase, 0x800F, port, 0x1f);

		val = read_phy_reg(regbase, 0x0029, port);
		write_phy_reg(regbase, 0x0029, port, val | (0x7 << 1));

		val = read_phy_reg(regbase, 0x0056, port);
		write_phy_reg(regbase, 0x0056, port, val & ~(1 << 3));

		val = read_phy_reg(regbase, 0x0018, port);
		write_phy_reg(regbase, 0x0018, port, val & ~(0x7 << 0));
	}
}