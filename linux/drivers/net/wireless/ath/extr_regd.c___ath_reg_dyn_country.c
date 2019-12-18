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
typedef  int /*<<< orphan*/  u16 ;
struct wiphy {int dummy; } ;
struct regulatory_request {scalar_t__ initiator; int /*<<< orphan*/  alpha2; } ;
struct ath_regulatory {int /*<<< orphan*/  current_rd; } ;

/* Variables and functions */
 int /*<<< orphan*/  COUNTRY_ERD_FLAG ; 
 int EINVAL ; 
 scalar_t__ NL80211_REGDOM_SET_BY_COUNTRY_IE ; 
 int /*<<< orphan*/  __ath_regd_init (struct ath_regulatory*) ; 
 int /*<<< orphan*/  ath_is_world_regd (struct ath_regulatory*) ; 
 int /*<<< orphan*/  ath_reg_apply_world_flags (struct wiphy*,scalar_t__,struct ath_regulatory*) ; 
 int /*<<< orphan*/  ath_regd_find_country_by_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __ath_reg_dyn_country(struct wiphy *wiphy,
				 struct ath_regulatory *reg,
				 struct regulatory_request *request)
{
	u16 country_code;

	if (request->initiator == NL80211_REGDOM_SET_BY_COUNTRY_IE &&
	    !ath_is_world_regd(reg))
		return -EINVAL;

	country_code = ath_regd_find_country_by_name(request->alpha2);
	if (country_code == (u16) -1)
		return -EINVAL;

	reg->current_rd = COUNTRY_ERD_FLAG;
	reg->current_rd |= country_code;

	__ath_regd_init(reg);

	ath_reg_apply_world_flags(wiphy, request->initiator, reg);

	return 0;
}