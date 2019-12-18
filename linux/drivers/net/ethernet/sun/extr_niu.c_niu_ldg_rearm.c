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
typedef  int /*<<< orphan*/  u64 ;
struct niu_ldg {int /*<<< orphan*/  ldg_num; int /*<<< orphan*/  timer; } ;
struct niu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LDG_IMGMT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LDG_IMGMT_ARM ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void niu_ldg_rearm(struct niu *np, struct niu_ldg *lp, int on)
{
	u64 val = (u64) lp->timer;

	if (on)
		val |= LDG_IMGMT_ARM;

	nw64(LDG_IMGMT(lp->ldg_num), val);
}