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
struct transform {int dummy; } ;
struct dce_transform {int /*<<< orphan*/ * filter_v; int /*<<< orphan*/ * filter_h; } ;

/* Variables and functions */
 struct dce_transform* TO_DCE_TRANSFORM (struct transform*) ; 

__attribute__((used)) static void dce_transform_reset(struct transform *xfm)
{
	struct dce_transform *xfm_dce = TO_DCE_TRANSFORM(xfm);

	xfm_dce->filter_h = NULL;
	xfm_dce->filter_v = NULL;
}