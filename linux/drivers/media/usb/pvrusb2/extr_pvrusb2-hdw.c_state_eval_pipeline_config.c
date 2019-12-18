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
struct pvr2_hdw {scalar_t__ state_pipeline_pause; scalar_t__ state_pipeline_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  pvr2_hdw_commit_execute (struct pvr2_hdw*) ; 

__attribute__((used)) static int state_eval_pipeline_config(struct pvr2_hdw *hdw)
{
	if (hdw->state_pipeline_config ||
	    hdw->state_pipeline_pause) return 0;
	pvr2_hdw_commit_execute(hdw);
	return !0;
}