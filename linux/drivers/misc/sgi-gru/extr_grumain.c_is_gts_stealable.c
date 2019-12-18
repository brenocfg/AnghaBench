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
 int down_write_trylock (int /*<<< orphan*/ *) ; 
 scalar_t__ is_kernel_context (struct gru_thread_state*) ; 
 int mutex_trylock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int is_gts_stealable(struct gru_thread_state *gts,
		struct gru_blade_state *bs)
{
	if (is_kernel_context(gts))
		return down_write_trylock(&bs->bs_kgts_sema);
	else
		return mutex_trylock(&gts->ts_ctxlock);
}