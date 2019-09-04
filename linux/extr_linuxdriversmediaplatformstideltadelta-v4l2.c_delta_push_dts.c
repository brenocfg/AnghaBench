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
struct delta_dts {int /*<<< orphan*/  list; int /*<<< orphan*/  val; } ;
struct delta_ctx {int /*<<< orphan*/  dts; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct delta_dts* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void delta_push_dts(struct delta_ctx *ctx, u64 val)
{
	struct delta_dts *dts;

	dts = kzalloc(sizeof(*dts), GFP_KERNEL);
	if (!dts)
		return;

	INIT_LIST_HEAD(&dts->list);

	/*
	 * protected by global lock acquired
	 * by V4L2 when calling delta_vb2_au_queue
	 */
	dts->val = val;
	list_add_tail(&dts->list, &ctx->dts);
}