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
struct bfad_s {int /*<<< orphan*/ * im; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfad_destroy_workq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

void
bfad_im_probe_undo(struct bfad_s *bfad)
{
	if (bfad->im) {
		bfad_destroy_workq(bfad->im);
		kfree(bfad->im);
		bfad->im = NULL;
	}
}