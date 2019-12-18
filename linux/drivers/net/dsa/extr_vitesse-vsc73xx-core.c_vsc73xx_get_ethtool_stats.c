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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct vsc73xx {int /*<<< orphan*/  dev; } ;
struct dsa_switch {struct vsc73xx* priv; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSC73XX_BLOCK_MAC ; 
 int /*<<< orphan*/  VSC73XX_C_RX0 ; 
 int /*<<< orphan*/  VSC73XX_C_RX1 ; 
 int /*<<< orphan*/  VSC73XX_C_RX2 ; 
 int /*<<< orphan*/  VSC73XX_C_TX0 ; 
 int /*<<< orphan*/  VSC73XX_C_TX1 ; 
 int /*<<< orphan*/  VSC73XX_C_TX2 ; 
 int /*<<< orphan*/  VSC73XX_RXOCT ; 
 int /*<<< orphan*/  VSC73XX_TXOCT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int vsc73xx_read (struct vsc73xx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vsc73xx_get_ethtool_stats(struct dsa_switch *ds, int port,
				      uint64_t *data)
{
	struct vsc73xx *vsc = ds->priv;
	u8 regs[] = {
		VSC73XX_RXOCT,
		VSC73XX_C_RX0,
		VSC73XX_C_RX1,
		VSC73XX_C_RX2,
		VSC73XX_TXOCT,
		VSC73XX_C_TX0,
		VSC73XX_C_TX1,
		VSC73XX_C_TX2,
	};
	u32 val;
	int ret;
	int i;

	for (i = 0; i < ARRAY_SIZE(regs); i++) {
		ret = vsc73xx_read(vsc, VSC73XX_BLOCK_MAC, port,
				   regs[i], &val);
		if (ret) {
			dev_err(vsc->dev, "error reading counter %d\n", i);
			return;
		}
		data[i] = val;
	}
}