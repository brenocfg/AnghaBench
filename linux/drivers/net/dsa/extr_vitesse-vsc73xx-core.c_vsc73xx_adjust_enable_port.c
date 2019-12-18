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
typedef  int u32 ;
struct vsc73xx {int dummy; } ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_ARBITER ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_MAC ; 
 int /*<<< orphan*/  VSC73XX_FCCONF ; 
 int VSC73XX_FCCONF_FLOW_CTRL_OBEY ; 
 int VSC73XX_FCCONF_ZERO_PAUSE_EN ; 
 int /*<<< orphan*/  VSC73XX_MAC_CFG ; 
 int VSC73XX_MAC_CFG_RESET ; 
 int VSC73XX_MAC_CFG_RX_EN ; 
 int VSC73XX_MAC_CFG_SEED_LOAD ; 
 int VSC73XX_MAC_CFG_SEED_OFFSET ; 
 int VSC73XX_MAC_CFG_TX_EN ; 
 int VSC73XX_MAC_CFG_WEXC_DIS ; 
 int /*<<< orphan*/  VSC73XX_SBACKWDROP ; 
 int /*<<< orphan*/  get_random_bytes (int*,int) ; 
 int /*<<< orphan*/  vsc73xx_update_bits (struct vsc73xx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  vsc73xx_write (struct vsc73xx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vsc73xx_adjust_enable_port(struct vsc73xx *vsc,
				       int port, struct phy_device *phydev,
				       u32 initval)
{
	u32 val = initval;
	u8 seed;

	/* Reset this port FIXME: break out subroutine */
	val |= VSC73XX_MAC_CFG_RESET;
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC, port, VSC73XX_MAC_CFG, val);

	/* Seed the port randomness with randomness */
	get_random_bytes(&seed, 1);
	val |= seed << VSC73XX_MAC_CFG_SEED_OFFSET;
	val |= VSC73XX_MAC_CFG_SEED_LOAD;
	val |= VSC73XX_MAC_CFG_WEXC_DIS;
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC, port, VSC73XX_MAC_CFG, val);

	/* Flow control for the PHY facing ports:
	 * Use a zero delay pause frame when pause condition is left
	 * Obey pause control frames
	 * When generating pause frames, use 0xff as pause value
	 */
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC, port, VSC73XX_FCCONF,
		      VSC73XX_FCCONF_ZERO_PAUSE_EN |
		      VSC73XX_FCCONF_FLOW_CTRL_OBEY |
		      0xff);

	/* Disallow backward dropping of frames from this port */
	vsc73xx_update_bits(vsc, VSC73XX_BLOCK_ARBITER, 0,
			    VSC73XX_SBACKWDROP, BIT(port), 0);

	/* Enable TX, RX, deassert reset, stop loading seed */
	vsc73xx_update_bits(vsc, VSC73XX_BLOCK_MAC, port,
			    VSC73XX_MAC_CFG,
			    VSC73XX_MAC_CFG_RESET | VSC73XX_MAC_CFG_SEED_LOAD |
			    VSC73XX_MAC_CFG_TX_EN | VSC73XX_MAC_CFG_RX_EN,
			    VSC73XX_MAC_CFG_TX_EN | VSC73XX_MAC_CFG_RX_EN);
}