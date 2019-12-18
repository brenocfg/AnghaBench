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
struct uclogic_params {int /*<<< orphan*/  frame; int /*<<< orphan*/  pen; int /*<<< orphan*/  pen_unused; int /*<<< orphan*/  desc_ptr; int /*<<< orphan*/  invalid; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct uclogic_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  uclogic_params_frame_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uclogic_params_pen_cleanup (int /*<<< orphan*/ *) ; 

void uclogic_params_cleanup(struct uclogic_params *params)
{
	if (!params->invalid) {
		kfree(params->desc_ptr);
		if (!params->pen_unused)
			uclogic_params_pen_cleanup(&params->pen);
		uclogic_params_frame_cleanup(&params->frame);
		memset(params, 0, sizeof(*params));
	}
}