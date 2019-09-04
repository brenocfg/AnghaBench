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
typedef  scalar_t__ u64 ;
struct throtl_grp {int dummy; } ;
struct seq_file {int dummy; } ;
struct blkg_policy_data {int dummy; } ;

/* Variables and functions */
 scalar_t__ U64_MAX ; 
 scalar_t__ __blkg_prfill_u64 (struct seq_file*,struct blkg_policy_data*,scalar_t__) ; 
 struct throtl_grp* pd_to_tg (struct blkg_policy_data*) ; 

__attribute__((used)) static u64 tg_prfill_conf_u64(struct seq_file *sf, struct blkg_policy_data *pd,
			      int off)
{
	struct throtl_grp *tg = pd_to_tg(pd);
	u64 v = *(u64 *)((void *)tg + off);

	if (v == U64_MAX)
		return 0;
	return __blkg_prfill_u64(sf, pd, v);
}