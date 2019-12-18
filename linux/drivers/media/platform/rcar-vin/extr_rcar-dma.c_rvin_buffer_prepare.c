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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct TYPE_2__ {unsigned long sizeimage; } ;
struct rvin_dev {TYPE_1__ format; } ;

/* Variables and functions */
 int EINVAL ; 
 struct rvin_dev* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 unsigned long vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vb2_set_plane_payload (struct vb2_buffer*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  vin_err (struct rvin_dev*,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int rvin_buffer_prepare(struct vb2_buffer *vb)
{
	struct rvin_dev *vin = vb2_get_drv_priv(vb->vb2_queue);
	unsigned long size = vin->format.sizeimage;

	if (vb2_plane_size(vb, 0) < size) {
		vin_err(vin, "buffer too small (%lu < %lu)\n",
			vb2_plane_size(vb, 0), size);
		return -EINVAL;
	}

	vb2_set_plane_payload(vb, 0, size);

	return 0;
}