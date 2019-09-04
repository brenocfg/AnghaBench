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
typedef  int u32 ;
struct vsc73xx {int* addr; } ;

/* Variables and functions */
 int CPU_PORT ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_MAC ; 
 int /*<<< orphan*/  VSC73XX_CAT_DROP ; 
 int VSC73XX_CAT_DROP_FWD_PAUSE_ENA ; 
 int /*<<< orphan*/  VSC73XX_C_RX0 ; 
 int /*<<< orphan*/  VSC73XX_FCCONF ; 
 int VSC73XX_FCCONF_FLOW_CTRL_OBEY ; 
 int VSC73XX_FCCONF_ZERO_PAUSE_EN ; 
 int /*<<< orphan*/  VSC73XX_FCMACHI ; 
 int /*<<< orphan*/  VSC73XX_FCMACLO ; 
 int /*<<< orphan*/  VSC73XX_MAC_CFG ; 
 int VSC73XX_MAC_CFG_1000M_F_PHY ; 
 int VSC73XX_MAC_CFG_1000M_F_RGMII ; 
 int VSC73XX_MAC_CFG_RESET ; 
 int VSC73XX_MAC_CFG_RX_EN ; 
 int VSC73XX_MAC_CFG_TX_EN ; 
 int /*<<< orphan*/  VSC73XX_MAXLEN ; 
 int /*<<< orphan*/  VSC73XX_Q_MISC_CONF ; 
 int VSC73XX_Q_MISC_CONF_EARLY_TX_512 ; 
 int VSC73XX_Q_MISC_CONF_EXTENT_MEM ; 
 int VSC73XX_Q_MISC_CONF_MAC_PAUSE_MODE ; 
 int /*<<< orphan*/  vsc73xx_write (struct vsc73xx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void vsc73xx_init_port(struct vsc73xx *vsc, int port)
{
	u32 val;

	/* MAC configure, first reset the port and then write defaults */
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_MAC_CFG,
		      VSC73XX_MAC_CFG_RESET);

	/* Take up the port in 1Gbit mode by default, this will be
	 * augmented after auto-negotiation on the PHY-facing
	 * ports.
	 */
	if (port == CPU_PORT)
		val = VSC73XX_MAC_CFG_1000M_F_RGMII;
	else
		val = VSC73XX_MAC_CFG_1000M_F_PHY;

	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_MAC_CFG,
		      val |
		      VSC73XX_MAC_CFG_TX_EN |
		      VSC73XX_MAC_CFG_RX_EN);

	/* Max length, we can do up to 9.6 KiB, so allow that.
	 * According to application not "VSC7398 Jumbo Frames" setting
	 * up the MTU to 9.6 KB does not affect the performance on standard
	 * frames, so just enable it. It is clear from the application note
	 * that "9.6 kilobytes" == 9600 bytes.
	 */
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_MAXLEN, 9600);

	/* Flow control for the CPU port:
	 * Use a zero delay pause frame when pause condition is left
	 * Obey pause control frames
	 */
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_FCCONF,
		      VSC73XX_FCCONF_ZERO_PAUSE_EN |
		      VSC73XX_FCCONF_FLOW_CTRL_OBEY);

	/* Issue pause control frames on PHY facing ports.
	 * Allow early initiation of MAC transmission if the amount
	 * of egress data is below 512 bytes on CPU port.
	 * FIXME: enable 20KiB buffers?
	 */
	if (port == CPU_PORT)
		val = VSC73XX_Q_MISC_CONF_EARLY_TX_512;
	else
		val = VSC73XX_Q_MISC_CONF_MAC_PAUSE_MODE;
	val |= VSC73XX_Q_MISC_CONF_EXTENT_MEM;
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_Q_MISC_CONF,
		      val);

	/* Flow control MAC: a MAC address used in flow control frames */
	val = (vsc->addr[5] << 16) | (vsc->addr[4] << 8) | (vsc->addr[3]);
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_FCMACHI,
		      val);
	val = (vsc->addr[2] << 16) | (vsc->addr[1] << 8) | (vsc->addr[0]);
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_FCMACLO,
		      val);

	/* Tell the categorizer to forward pause frames, not control
	 * frame. Do not drop anything.
	 */
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC,
		      port,
		      VSC73XX_CAT_DROP,
		      VSC73XX_CAT_DROP_FWD_PAUSE_ENA);

	/* Clear all counters */
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC,
		      port, VSC73XX_C_RX0, 0);
}