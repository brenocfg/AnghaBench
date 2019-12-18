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
struct vb2_buffer {int /*<<< orphan*/  vb2_queue; } ;
struct pwc_device {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENODEV ; 
 struct pwc_device* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int buffer_prepare(struct vb2_buffer *vb)
{
	struct pwc_device *pdev = vb2_get_drv_priv(vb->vb2_queue);

	/* Don't allow queueing new buffers after device disconnection */
	if (!pdev->udev)
		return -ENODEV;

	return 0;
}