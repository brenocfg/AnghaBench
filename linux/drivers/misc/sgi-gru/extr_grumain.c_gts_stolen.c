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
struct gru_thread_state {int /*<<< orphan*/  ts_ctxlock; } ;
struct gru_blade_state {int /*<<< orphan*/  bs_kgts_sema; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 scalar_t__ is_kernel_context (struct gru_thread_state*) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  steal_kernel_context ; 
 int /*<<< orphan*/  steal_user_context ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gts_stolen(struct gru_thread_state *gts,
		struct gru_blade_state *bs)
{
	if (is_kernel_context(gts)) {
		up_write(&bs->bs_kgts_sema);
		STAT(steal_kernel_context);
	} else {
		mutex_unlock(&gts->ts_ctxlock);
		STAT(steal_user_context);
	}
}