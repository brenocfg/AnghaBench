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
 size_t CI_ROLE_HOST ; 
 int /*<<< orphan*/  DCCPARAMS_HC ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ci_role_driver* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_irq ; 
 int /*<<< orphan*/  host_start ; 
 int /*<<< orphan*/  host_stop ; 
 int /*<<< orphan*/  hw_read (struct ci_hdrc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ci_hdrc_host_init(struct ci_hdrc *ci)
{
	struct ci_role_driver *rdrv;

	if (!hw_read(ci, CAP_DCCPARAMS, DCCPARAMS_HC))
		return -ENXIO;

	rdrv = devm_kzalloc(ci->dev, sizeof(struct ci_role_driver), GFP_KERNEL);
	if (!rdrv)
		return -ENOMEM;

	rdrv->start	= host_start;
	rdrv->stop	= host_stop;
	rdrv->irq	= host_irq;
	rdrv->name	= "host";
	ci->roles[CI_ROLE_HOST] = rdrv;

	return 0;
}