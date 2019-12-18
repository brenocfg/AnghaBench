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
struct gspca_dev {TYPE_1__* sd_desc; scalar_t__ present; scalar_t__ usb_err; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* dq_callback ) (struct gspca_dev*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct gspca_dev*) ; 
 struct gspca_dev* vb2_get_drv_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void gspca_buffer_finish(struct vb2_buffer *vb)
{
	struct gspca_dev *gspca_dev = vb2_get_drv_priv(vb->vb2_queue);

	if (!gspca_dev->sd_desc->dq_callback)
		return;

	gspca_dev->usb_err = 0;
	if (gspca_dev->present)
		gspca_dev->sd_desc->dq_callback(gspca_dev);
}