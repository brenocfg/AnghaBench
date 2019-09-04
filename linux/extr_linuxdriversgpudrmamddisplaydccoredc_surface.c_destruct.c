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
struct dc_plane_state {int /*<<< orphan*/ * in_transfer_func; int /*<<< orphan*/ * gamma_correction; } ;

/* Variables and functions */
 int /*<<< orphan*/  dc_gamma_release (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dc_transfer_func_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destruct(struct dc_plane_state *plane_state)
{
	if (plane_state->gamma_correction != NULL) {
		dc_gamma_release(&plane_state->gamma_correction);
	}
	if (plane_state->in_transfer_func != NULL) {
		dc_transfer_func_release(
				plane_state->in_transfer_func);
		plane_state->in_transfer_func = NULL;
	}
}