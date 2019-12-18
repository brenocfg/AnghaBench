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
struct gru_blade_state {int /*<<< orphan*/  bs_kgts_sema; int /*<<< orphan*/ * bs_async_wq; scalar_t__ bs_async_cbrs; scalar_t__ bs_async_dsr_bytes; } ;

/* Variables and functions */
 struct gru_blade_state* ASYNC_HAN_TO_BS (unsigned long) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 

void gru_release_async_resources(unsigned long han)
{
	struct gru_blade_state *bs = ASYNC_HAN_TO_BS(han);

	down_write(&bs->bs_kgts_sema);
	bs->bs_async_dsr_bytes = 0;
	bs->bs_async_cbrs = 0;
	bs->bs_async_wq = NULL;
	up_write(&bs->bs_kgts_sema);
}