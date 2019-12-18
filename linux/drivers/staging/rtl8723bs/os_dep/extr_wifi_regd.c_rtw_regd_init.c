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
struct wiphy {int dummy; } ;
struct adapter {TYPE_1__* rtw_wdev; } ;
struct TYPE_2__ {struct wiphy* wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _rtw_regd_init_wiphy (int /*<<< orphan*/ *,struct wiphy*,void (*) (struct wiphy*,struct regulatory_request*)) ; 

int rtw_regd_init(struct adapter *padapter,
		  void (*reg_notifier)(struct wiphy *wiphy,
				       struct regulatory_request *request))
{
	struct wiphy *wiphy = padapter->rtw_wdev->wiphy;

	_rtw_regd_init_wiphy(NULL, wiphy, reg_notifier);

	return 0;
}