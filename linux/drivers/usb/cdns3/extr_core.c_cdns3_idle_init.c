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
struct cdns3_role_driver {char* name; int /*<<< orphan*/ * resume; int /*<<< orphan*/ * suspend; int /*<<< orphan*/  state; int /*<<< orphan*/  stop; int /*<<< orphan*/  start; } ;
struct cdns3 {struct cdns3_role_driver** roles; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CDNS3_ROLE_STATE_INACTIVE ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t USB_ROLE_NONE ; 
 int /*<<< orphan*/  cdns3_idle_role_start ; 
 int /*<<< orphan*/  cdns3_idle_role_stop ; 
 struct cdns3_role_driver* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cdns3_idle_init(struct cdns3 *cdns)
{
	struct cdns3_role_driver *rdrv;

	rdrv = devm_kzalloc(cdns->dev, sizeof(*rdrv), GFP_KERNEL);
	if (!rdrv)
		return -ENOMEM;

	rdrv->start = cdns3_idle_role_start;
	rdrv->stop = cdns3_idle_role_stop;
	rdrv->state = CDNS3_ROLE_STATE_INACTIVE;
	rdrv->suspend = NULL;
	rdrv->resume = NULL;
	rdrv->name = "idle";

	cdns->roles[USB_ROLE_NONE] = rdrv;

	return 0;
}