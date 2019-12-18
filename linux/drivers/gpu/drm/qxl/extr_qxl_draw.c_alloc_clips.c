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
struct qxl_release {int dummy; } ;
struct qxl_rect {int dummy; } ;
struct qxl_device {int dummy; } ;
struct qxl_clip_rects {int dummy; } ;
struct qxl_bo {int dummy; } ;

/* Variables and functions */
 int qxl_alloc_bo_reserved (struct qxl_device*,struct qxl_release*,int,struct qxl_bo**) ; 

__attribute__((used)) static int alloc_clips(struct qxl_device *qdev,
		       struct qxl_release *release,
		       unsigned int num_clips,
		       struct qxl_bo **clips_bo)
{
	int size = sizeof(struct qxl_clip_rects) + sizeof(struct qxl_rect) * num_clips;

	return qxl_alloc_bo_reserved(qdev, release, size, clips_bo);
}