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
struct gru_tlb_global_handle {int dummy; } ;
struct gru_state {int /*<<< orphan*/  gs_gid; } ;

/* Variables and functions */
 scalar_t__ GRUMAXINVAL ; 
 struct gru_tlb_global_handle* get_lock_tgh_handle (struct gru_state*) ; 
 int /*<<< orphan*/  get_unlock_tgh_handle (struct gru_tlb_global_handle*) ; 
 int /*<<< orphan*/  gru_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  grudev ; 
 int /*<<< orphan*/  tgh_invalidate (struct gru_tlb_global_handle*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__,int) ; 

void gru_flush_all_tlb(struct gru_state *gru)
{
	struct gru_tlb_global_handle *tgh;

	gru_dbg(grudev, "gid %d\n", gru->gs_gid);
	tgh = get_lock_tgh_handle(gru);
	tgh_invalidate(tgh, 0, ~0, 0, 1, 1, GRUMAXINVAL - 1, 0xffff);
	get_unlock_tgh_handle(tgh);
}