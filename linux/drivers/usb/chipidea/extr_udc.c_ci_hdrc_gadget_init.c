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
struct ci_role_driver {char* name; int /*<<< orphan*/  irq; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct ci_hdrc {struct ci_role_driver** roles; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_DCCPARAMS ; 
 size_t CI_ROLE_GADGET ; 
 int /*<<< orphan*/  DCCPARAMS_DC ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ci_role_driver* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udc_id_switch_for_device ; 
 int /*<<< orphan*/  udc_id_switch_for_host ; 
 int /*<<< orphan*/  udc_irq ; 
 int udc_start (struct ci_hdrc*) ; 

int ci_hdrc_gadget_init(struct ci_hdrc *ci)
{
	struct ci_role_driver *rdrv;
	int ret;

	if (!hw_read(ci, CAP_DCCPARAMS, DCCPARAMS_DC))
		return -ENXIO;

	rdrv = devm_kzalloc(ci->dev, sizeof(*rdrv), GFP_KERNEL);
	if (!rdrv)
		return -ENOMEM;

	rdrv->start	= udc_id_switch_for_device;
	rdrv->stop	= udc_id_switch_for_host;
	rdrv->irq	= udc_irq;
	rdrv->name	= "gadget";

	ret = udc_start(ci);
	if (!ret)
		ci->roles[CI_ROLE_GADGET] = rdrv;

	return ret;
}