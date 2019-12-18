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
struct file {struct cx231xx_fh* private_data; } ;
struct cx231xx_fh {int /*<<< orphan*/  vidq; struct cx231xx* dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  max_pkt_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_pkt_size; } ;
struct cx231xx {TYPE_2__ ts1_mode; TYPE_1__ video_mode; scalar_t__ USE_ISO; } ;
typedef  enum v4l2_buf_type { ____Placeholder_v4l2_buf_type } v4l2_buf_type ;

/* Variables and functions */
 int /*<<< orphan*/  CX231XX_DIGITAL_MODE ; 
 int /*<<< orphan*/  CX231XX_NUM_BUFS ; 
 int /*<<< orphan*/  CX231XX_NUM_PACKETS ; 
 int /*<<< orphan*/  INDEX_TS1 ; 
 int /*<<< orphan*/  cx231xx_bulk_copy ; 
 int /*<<< orphan*/  cx231xx_init_bulk (struct cx231xx*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_init_isoc (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_isoc_copy ; 
 int /*<<< orphan*/  cx231xx_set_alt_setting (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx231xx_set_mode (struct cx231xx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (int,char*) ; 
 int videobuf_streamon (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vidioc_streamon(struct file *file, void *priv,
				enum v4l2_buf_type i)
{
	struct cx231xx_fh  *fh  = file->private_data;
	struct cx231xx *dev = fh->dev;

	dprintk(3, "enter vidioc_streamon()\n");
	cx231xx_set_alt_setting(dev, INDEX_TS1, 0);
	cx231xx_set_mode(dev, CX231XX_DIGITAL_MODE);
	if (dev->USE_ISO)
		cx231xx_init_isoc(dev, CX231XX_NUM_PACKETS,
				CX231XX_NUM_BUFS,
				dev->video_mode.max_pkt_size,
				cx231xx_isoc_copy);
	else {
		cx231xx_init_bulk(dev, 320,
				5,
				dev->ts1_mode.max_pkt_size,
				cx231xx_bulk_copy);
	}
	dprintk(3, "exit vidioc_streamon()\n");
	return videobuf_streamon(&fh->vidq);
}