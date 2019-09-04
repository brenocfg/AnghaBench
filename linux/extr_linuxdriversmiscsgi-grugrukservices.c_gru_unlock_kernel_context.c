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
struct gru_blade_state {int /*<<< orphan*/  bs_kgts_sema; } ;

/* Variables and functions */
 int /*<<< orphan*/  STAT (int /*<<< orphan*/ ) ; 
 struct gru_blade_state** gru_base ; 
 int /*<<< orphan*/  unlock_kernel_context ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gru_unlock_kernel_context(int blade_id)
{
	struct gru_blade_state *bs;

	bs = gru_base[blade_id];
	up_read(&bs->bs_kgts_sema);
	STAT(unlock_kernel_context);
}