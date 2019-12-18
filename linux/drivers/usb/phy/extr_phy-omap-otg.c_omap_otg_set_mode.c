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
struct otg_device {int /*<<< orphan*/  id; scalar_t__ vbus; } ;

/* Variables and functions */
 int OMAP_OTG_ASESSVLD ; 
 int OMAP_OTG_BSESSEND ; 
 int OMAP_OTG_BSESSVLD ; 
 int OMAP_OTG_ID ; 
 int /*<<< orphan*/  omap_otg_ctrl (struct otg_device*,int) ; 

__attribute__((used)) static void omap_otg_set_mode(struct otg_device *otg_dev)
{
	if (!otg_dev->id && otg_dev->vbus)
		/* Set B-session valid. */
		omap_otg_ctrl(otg_dev, OMAP_OTG_ID | OMAP_OTG_BSESSVLD);
	else if (otg_dev->vbus)
		/* Set A-session valid. */
		omap_otg_ctrl(otg_dev, OMAP_OTG_ASESSVLD);
	else if (!otg_dev->id)
		/* Set B-session end to indicate no VBUS. */
		omap_otg_ctrl(otg_dev, OMAP_OTG_ID | OMAP_OTG_BSESSEND);
}