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
struct vb2_queue {struct saa7134_dmaqueue* drv_priv; } ;
struct saa7134_dmaqueue {struct saa7134_dev* dev; } ;
struct saa7134_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  saa7134_stop_streaming (struct saa7134_dev*,struct saa7134_dmaqueue*) ; 
 int /*<<< orphan*/  saa7134_ts_stop (struct saa7134_dev*) ; 

void saa7134_ts_stop_streaming(struct vb2_queue *vq)
{
	struct saa7134_dmaqueue *dmaq = vq->drv_priv;
	struct saa7134_dev *dev = dmaq->dev;

	saa7134_ts_stop(dev);
	saa7134_stop_streaming(dev, dmaq);
}