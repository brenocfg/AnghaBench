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
typedef  scalar_t__ v4l2_std_id ;
struct pvr2_hdw {int /*<<< orphan*/  v4l2_dev; scalar_t__ std_mask_avail; } ;

/* Variables and functions */
 int /*<<< orphan*/  querystd ; 
 int /*<<< orphan*/  v4l2_device_call_all (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  video ; 

__attribute__((used)) static v4l2_std_id pvr2_hdw_get_detected_std(struct pvr2_hdw *hdw)
{
	v4l2_std_id std;
	std = (v4l2_std_id)hdw->std_mask_avail;
	v4l2_device_call_all(&hdw->v4l2_dev, 0,
			     video, querystd, &std);
	return std;
}