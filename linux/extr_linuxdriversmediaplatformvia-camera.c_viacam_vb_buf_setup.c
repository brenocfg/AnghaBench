#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct videobuf_queue {struct via_camera* priv_data; } ;
struct TYPE_2__ {unsigned int sizeimage; } ;
struct via_camera {TYPE_1__ user_format; } ;

/* Variables and functions */

__attribute__((used)) static int viacam_vb_buf_setup(struct videobuf_queue *q,
		unsigned int *count, unsigned int *size)
{
	struct via_camera *cam = q->priv_data;

	*size = cam->user_format.sizeimage;
	if (*count == 0 || *count > 6)	/* Arbitrary number */
		*count = 6;
	return 0;
}