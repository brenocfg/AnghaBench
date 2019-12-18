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
typedef  int u64 ;
struct ar9170 {int cur_mc_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  AR9170_MAC_REG_GROUP_HASH_TBL_H ; 
 int /*<<< orphan*/  AR9170_MAC_REG_GROUP_HASH_TBL_L ; 
 int /*<<< orphan*/  carl9170_regwrite (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  carl9170_regwrite_begin (struct ar9170*) ; 
 int /*<<< orphan*/  carl9170_regwrite_finish () ; 
 int carl9170_regwrite_result () ; 

int carl9170_update_multicast(struct ar9170 *ar, const u64 mc_hash)
{
	int err;

	carl9170_regwrite_begin(ar);
	carl9170_regwrite(AR9170_MAC_REG_GROUP_HASH_TBL_H, mc_hash >> 32);
	carl9170_regwrite(AR9170_MAC_REG_GROUP_HASH_TBL_L, mc_hash);
	carl9170_regwrite_finish();
	err = carl9170_regwrite_result();
	if (err)
		return err;

	ar->cur_mc_hash = mc_hash;
	return 0;
}