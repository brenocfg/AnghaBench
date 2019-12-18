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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct net_device {int dummy; } ;
struct dcb_app {scalar_t__ selector; scalar_t__ priority; int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 scalar_t__ DCB_APP_IDTYPE_ETHTYPE ; 
 scalar_t__ DCB_APP_IDTYPE_PORTNUM ; 
 int EINVAL ; 
 int __cxgb4_setapp (struct net_device*,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int dcb_setapp (struct net_device*,struct dcb_app*) ; 

__attribute__((used)) static int cxgb4_setapp(struct net_device *dev, u8 app_idtype, u16 app_id,
			u8 app_prio)
{
	int ret;
	struct dcb_app app = {
		.selector = app_idtype,
		.protocol = app_id,
		.priority = app_prio,
	};

	if (app_idtype != DCB_APP_IDTYPE_ETHTYPE &&
	    app_idtype != DCB_APP_IDTYPE_PORTNUM)
		return -EINVAL;

	/* Convert app_idtype to a format that firmware understands */
	ret = __cxgb4_setapp(dev, app_idtype == DCB_APP_IDTYPE_ETHTYPE ?
			      app_idtype : 3, app_id, app_prio);
	if (ret)
		return ret;

	return dcb_setapp(dev, &app);
}