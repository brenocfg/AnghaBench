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
struct pvr2_hdw {scalar_t__ state_pipeline_req; } ;

/* Variables and functions */

int pvr2_hdw_get_streaming(struct pvr2_hdw *hdw)
{
	return hdw->state_pipeline_req != 0;
}