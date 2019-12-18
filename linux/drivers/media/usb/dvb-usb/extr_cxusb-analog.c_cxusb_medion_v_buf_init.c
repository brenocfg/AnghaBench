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
struct dvb_usb_device {struct cxusb_medion_dev* priv; } ;
struct cxusb_medion_dev {int width; int height; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  OPS ; 
 int /*<<< orphan*/  cxusb_vprintk (struct dvb_usb_device*,int /*<<< orphan*/ ,char*) ; 
 struct dvb_usb_device* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 
 int vb2_plane_size (struct vb2_buffer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cxusb_medion_v_buf_init(struct vb2_buffer *vb)
{
	struct dvb_usb_device *dvbdev = vb2_get_drv_priv(vb->vb2_queue);
	struct cxusb_medion_dev *cxdev = dvbdev->priv;

	cxusb_vprintk(dvbdev, OPS, "buffer init\n");

	if (vb2_plane_size(vb, 0) < cxdev->width * cxdev->height * 2)
		return -ENOMEM;

	cxusb_vprintk(dvbdev, OPS, "buffer OK\n");

	return 0;
}