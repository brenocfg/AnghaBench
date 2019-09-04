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
struct throtl_grp {int dummy; } ;
struct blkcg_gq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  blkcg_policy_throtl ; 
 int /*<<< orphan*/  blkg_to_pd (struct blkcg_gq*,int /*<<< orphan*/ *) ; 
 struct throtl_grp* pd_to_tg (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct throtl_grp *blkg_to_tg(struct blkcg_gq *blkg)
{
	return pd_to_tg(blkg_to_pd(blkg, &blkcg_policy_throtl));
}