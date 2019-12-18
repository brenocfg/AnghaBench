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
struct rtl2832_sdr_dev {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int ENODEV ; 
 struct rtl2832_sdr_dev* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl2832_sdr_buf_prepare(struct vb2_buffer *vb)
{
	struct rtl2832_sdr_dev *dev = vb2_get_drv_priv(vb->vb2_queue);

	/* Don't allow queueing new buffers after device disconnection */
	if (!dev->udev)
		return -ENODEV;

	return 0;
}