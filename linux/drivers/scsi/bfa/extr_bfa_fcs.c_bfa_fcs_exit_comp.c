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
struct bfad_s {int /*<<< orphan*/  comp; } ;
struct bfa_fcs_s {struct bfad_s* bfad; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_fcs_exit_comp(void *fcs_cbarg)
{
	struct bfa_fcs_s      *fcs = fcs_cbarg;
	struct bfad_s         *bfad = fcs->bfad;

	complete(&bfad->comp);
}