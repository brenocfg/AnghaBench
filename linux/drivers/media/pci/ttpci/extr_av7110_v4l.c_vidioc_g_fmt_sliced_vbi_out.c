#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_sliced_vbi_data {int dummy; } ;
struct TYPE_4__ {int io_size; void*** service_lines; void* service_set; } ;
struct TYPE_3__ {TYPE_2__ sliced; } ;
struct v4l2_format {TYPE_1__ fmt; } ;
struct saa7146_fh {struct saa7146_dev* dev; } ;
struct saa7146_dev {scalar_t__ ext_priv; } ;
struct file {int dummy; } ;
struct av7110 {scalar_t__ wssMode; int /*<<< orphan*/  arm_app; } ;

/* Variables and functions */
 int EINVAL ; 
 int FW_VERSION (int /*<<< orphan*/ ) ; 
 void* V4L2_SLICED_WSS_625 ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int vidioc_g_fmt_sliced_vbi_out(struct file *file, void *fh,
					struct v4l2_format *f)
{
	struct saa7146_dev *dev = ((struct saa7146_fh *)fh)->dev;
	struct av7110 *av7110 = (struct av7110 *)dev->ext_priv;

	dprintk(2, "VIDIOC_G_FMT:\n");
	if (FW_VERSION(av7110->arm_app) < 0x2623)
		return -EINVAL;
	memset(&f->fmt.sliced, 0, sizeof f->fmt.sliced);
	if (av7110->wssMode) {
		f->fmt.sliced.service_set = V4L2_SLICED_WSS_625;
		f->fmt.sliced.service_lines[0][23] = V4L2_SLICED_WSS_625;
		f->fmt.sliced.io_size = sizeof(struct v4l2_sliced_vbi_data);
	}
	return 0;
}