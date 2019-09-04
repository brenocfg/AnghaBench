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
struct net_device {int dummy; } ;
struct dcb_app {scalar_t__ selector; int priority; scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  CXGB4_DCB_FW_APP_ID ; 
 int EINVAL ; 
 scalar_t__ IEEE_8021QAZ_APP_SEL_ANY ; 
 scalar_t__ IEEE_8021QAZ_APP_SEL_ETHERTYPE ; 
 int __cxgb4_setapp (struct net_device*,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  cxgb4_ieee_negotiation_complete (struct net_device*,int /*<<< orphan*/ ) ; 
 int dcb_ieee_setapp (struct net_device*,struct dcb_app*) ; 

__attribute__((used)) static int cxgb4_ieee_setapp(struct net_device *dev, struct dcb_app *app)
{
	int ret;

	if (!cxgb4_ieee_negotiation_complete(dev, CXGB4_DCB_FW_APP_ID))
		return -EINVAL;
	if (!(app->selector && app->protocol))
		return -EINVAL;

	if (!(app->selector > IEEE_8021QAZ_APP_SEL_ETHERTYPE  &&
	      app->selector < IEEE_8021QAZ_APP_SEL_ANY))
		return -EINVAL;

	/* change selector to a format that firmware understands */
	ret = __cxgb4_setapp(dev, app->selector - 1, app->protocol,
			     (1 << app->priority));
	if (ret)
		return ret;

	return dcb_ieee_setapp(dev, app);
}