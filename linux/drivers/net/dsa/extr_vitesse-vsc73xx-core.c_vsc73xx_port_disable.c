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
struct vsc73xx {int dummy; } ;
struct dsa_switch {struct vsc73xx* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  VSC73XX_BLOCK_MAC ; 
 int /*<<< orphan*/  VSC73XX_MAC_CFG ; 
 int /*<<< orphan*/  VSC73XX_MAC_CFG_RESET ; 
 int /*<<< orphan*/  vsc73xx_write (struct vsc73xx*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vsc73xx_port_disable(struct dsa_switch *ds, int port)
{
	struct vsc73xx *vsc = ds->priv;

	/* Just put the port into reset */
	vsc73xx_write(vsc, VSC73XX_BLOCK_MAC, port,
		      VSC73XX_MAC_CFG, VSC73XX_MAC_CFG_RESET);
}