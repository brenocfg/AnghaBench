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
struct vsc73xx {int /*<<< orphan*/  dev; } ;
struct phy_device {int dummy; } ;
struct dsa_switch {struct vsc73xx* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  vsc73xx_init_port (struct vsc73xx*,int) ; 

__attribute__((used)) static int vsc73xx_port_enable(struct dsa_switch *ds, int port,
			       struct phy_device *phy)
{
	struct vsc73xx *vsc = ds->priv;

	dev_info(vsc->dev, "enable port %d\n", port);
	vsc73xx_init_port(vsc, port);

	return 0;
}