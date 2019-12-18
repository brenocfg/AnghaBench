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
struct vb2_queue {int dummy; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int vb2_core_streamon (struct vb2_queue*,int) ; 
 scalar_t__ vb2_fileio_is_active (struct vb2_queue*) ; 

int vb2_streamon(struct vb2_queue *q, enum v4l2_buf_type type)
{
	if (vb2_fileio_is_active(q)) {
		dprintk(1, "file io in progress\n");
		return -EBUSY;
	}
	return vb2_core_streamon(q, type);
}