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
struct vb2_queue {struct cx23885_dev* drv_priv; } ;
struct cx23885_dev {int /*<<< orphan*/  ts1; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX2341X_ENC_STOP_CAPTURE ; 
 int /*<<< orphan*/  CX23885_END_NOW ; 
 int /*<<< orphan*/  CX23885_MPEG_CAPTURE ; 
 int /*<<< orphan*/  CX23885_RAW_BITS_NONE ; 
 int /*<<< orphan*/  cx23885_417_check_encoder (struct cx23885_dev*) ; 
 int /*<<< orphan*/  cx23885_api_cmd (struct cx23885_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23885_cancel_buffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 

__attribute__((used)) static void cx23885_stop_streaming(struct vb2_queue *q)
{
	struct cx23885_dev *dev = q->drv_priv;

	/* stop mpeg capture */
	cx23885_api_cmd(dev, CX2341X_ENC_STOP_CAPTURE, 3, 0,
			CX23885_END_NOW, CX23885_MPEG_CAPTURE,
			CX23885_RAW_BITS_NONE);

	msleep(500);
	cx23885_417_check_encoder(dev);
	cx23885_cancel_buffers(&dev->ts1);
}