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
struct wiphy {void (* reg_notifier ) (struct wiphy*,struct regulatory_request*) ;int /*<<< orphan*/  regulatory_flags; } ;
struct rtw_regulatory {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REGULATORY_CUSTOM_REG ; 
 int /*<<< orphan*/  REGULATORY_DISABLE_BEACON_HINTS ; 
 int /*<<< orphan*/  REGULATORY_STRICT_REG ; 
 int /*<<< orphan*/  rtw_regd_apply_hw_cap_flags (struct wiphy*) ; 

__attribute__((used)) static int
rtw_regd_init_wiphy(struct rtw_regulatory *reg, struct wiphy *wiphy,
		    void (*reg_notifier)(struct wiphy *wiphy,
					 struct regulatory_request *request))
{
	wiphy->reg_notifier = reg_notifier;

	wiphy->regulatory_flags &= ~REGULATORY_CUSTOM_REG;
	wiphy->regulatory_flags &= ~REGULATORY_STRICT_REG;
	wiphy->regulatory_flags &= ~REGULATORY_DISABLE_BEACON_HINTS;

	rtw_regd_apply_hw_cap_flags(wiphy);

	return 0;
}