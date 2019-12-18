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
struct gru_state {int gs_tgh_local_shift; int gs_tgh_first_remote; int /*<<< orphan*/  gs_blade_id; } ;

/* Variables and functions */
 int MAX_LOCAL_TGH ; 
 int fls (int) ; 
 int max (int /*<<< orphan*/ ,int) ; 
 int uv_blade_nr_possible_cpus (int /*<<< orphan*/ ) ; 

void gru_tgh_flush_init(struct gru_state *gru)
{
	int cpus, shift = 0, n;

	cpus = uv_blade_nr_possible_cpus(gru->gs_blade_id);

	/* n = cpus rounded up to next power of 2 */
	if (cpus) {
		n = 1 << fls(cpus - 1);

		/*
		 * shift count for converting local cpu# to TGH index
		 *      0 if cpus <= MAX_LOCAL_TGH,
		 *      1 if cpus <= 2*MAX_LOCAL_TGH,
		 *      etc
		 */
		shift = max(0, fls(n - 1) - fls(MAX_LOCAL_TGH - 1));
	}
	gru->gs_tgh_local_shift = shift;

	/* first starting TGH index to use for remote purges */
	gru->gs_tgh_first_remote = (cpus + (1 << shift) - 1) >> shift;

}