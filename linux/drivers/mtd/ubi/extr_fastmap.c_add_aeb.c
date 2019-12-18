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
struct ubi_attach_info {scalar_t__ max_ec; scalar_t__ min_ec; int /*<<< orphan*/  ec_count; int /*<<< orphan*/  ec_sum; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;
struct ubi_ainf_peb {int lnum; int scrub; scalar_t__ ec; TYPE_1__ u; scalar_t__ sqnum; scalar_t__ copy_flag; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 struct ubi_ainf_peb* ubi_alloc_aeb (struct ubi_attach_info*,int,int) ; 

__attribute__((used)) static int add_aeb(struct ubi_attach_info *ai, struct list_head *list,
		   int pnum, int ec, int scrub)
{
	struct ubi_ainf_peb *aeb;

	aeb = ubi_alloc_aeb(ai, pnum, ec);
	if (!aeb)
		return -ENOMEM;

	aeb->lnum = -1;
	aeb->scrub = scrub;
	aeb->copy_flag = aeb->sqnum = 0;

	ai->ec_sum += aeb->ec;
	ai->ec_count++;

	if (ai->max_ec < aeb->ec)
		ai->max_ec = aeb->ec;

	if (ai->min_ec > aeb->ec)
		ai->min_ec = aeb->ec;

	list_add_tail(&aeb->u.list, list);

	return 0;
}