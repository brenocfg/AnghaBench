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
typedef  int u32 ;
struct i915_syncmap {int /*<<< orphan*/  bitmap; scalar_t__ parent; int /*<<< orphan*/  prefix; scalar_t__ height; } ;

/* Variables and functions */
 int EINVAL ; 
 int check_seqno (struct i915_syncmap*,int /*<<< orphan*/ ,int) ; 
 int hweight32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i915_syncmap_is_later (struct i915_syncmap**,int /*<<< orphan*/ ,int) ; 
 int i915_syncmap_set (struct i915_syncmap**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ilog2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int check_one(struct i915_syncmap **sync, u64 context, u32 seqno)
{
	int err;

	err = i915_syncmap_set(sync, context, seqno);
	if (err)
		return err;

	if ((*sync)->height) {
		pr_err("Inserting first context=%llx did not return leaf (height=%d, prefix=%llx\n",
		       context, (*sync)->height, (*sync)->prefix);
		return -EINVAL;
	}

	if ((*sync)->parent) {
		pr_err("Inserting first context=%llx created branches!\n",
		       context);
		return -EINVAL;
	}

	if (hweight32((*sync)->bitmap) != 1) {
		pr_err("First bitmap does not contain a single entry, found %x (count=%d)!\n",
		       (*sync)->bitmap, hweight32((*sync)->bitmap));
		return -EINVAL;
	}

	err = check_seqno((*sync), ilog2((*sync)->bitmap), seqno);
	if (err)
		return err;

	if (!i915_syncmap_is_later(sync, context, seqno)) {
		pr_err("Lookup of first context=%llx/seqno=%x failed!\n",
		       context, seqno);
		return -EINVAL;
	}

	return 0;
}