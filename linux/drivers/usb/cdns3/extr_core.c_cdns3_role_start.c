#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cdns3 {int role; int /*<<< orphan*/  mutex; TYPE_1__** roles; } ;
typedef  enum usb_role { ____Placeholder_usb_role } usb_role ;
struct TYPE_2__ {scalar_t__ state; int (* start ) (struct cdns3*) ;} ;

/* Variables and functions */
 scalar_t__ CDNS3_ROLE_STATE_ACTIVE ; 
 int ENXIO ; 
 int USB_ROLE_DEVICE ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct cdns3*) ; 

__attribute__((used)) static int cdns3_role_start(struct cdns3 *cdns, enum usb_role role)
{
	int ret;

	if (WARN_ON(role > USB_ROLE_DEVICE))
		return 0;

	mutex_lock(&cdns->mutex);
	cdns->role = role;
	mutex_unlock(&cdns->mutex);

	if (!cdns->roles[role])
		return -ENXIO;

	if (cdns->roles[role]->state == CDNS3_ROLE_STATE_ACTIVE)
		return 0;

	mutex_lock(&cdns->mutex);
	ret = cdns->roles[role]->start(cdns);
	if (!ret)
		cdns->roles[role]->state = CDNS3_ROLE_STATE_ACTIVE;
	mutex_unlock(&cdns->mutex);

	return ret;
}