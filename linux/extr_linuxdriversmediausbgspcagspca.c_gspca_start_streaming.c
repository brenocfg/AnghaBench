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
struct gspca_dev {scalar_t__ sequence; } ;

/* Variables and functions */
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int gspca_init_transfer (struct gspca_dev*) ; 
 int /*<<< orphan*/  gspca_return_all_buffers (struct gspca_dev*,int /*<<< orphan*/ ) ; 
 struct gspca_dev* vb2_get_drv_priv (struct vb2_queue*) ; 

__attribute__((used)) static int gspca_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct gspca_dev *gspca_dev = vb2_get_drv_priv(vq);
	int ret;

	gspca_dev->sequence = 0;

	ret = gspca_init_transfer(gspca_dev);
	if (ret)
		gspca_return_all_buffers(gspca_dev, VB2_BUF_STATE_QUEUED);
	return ret;
}