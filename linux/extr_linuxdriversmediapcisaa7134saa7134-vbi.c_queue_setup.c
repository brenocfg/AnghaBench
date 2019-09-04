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
struct vb2_queue {struct saa7134_dmaqueue* drv_priv; } ;
struct saa7134_dmaqueue {struct saa7134_dev* dev; } ;
struct saa7134_dev {int vbi_vlen; int vbi_hlen; TYPE_1__* tvnorm; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int vbi_v_stop_0; int vbi_v_start_0; } ;

/* Variables and functions */
 int VBI_LINE_COUNT ; 
 int VBI_LINE_LENGTH ; 
 unsigned int saa7134_buffer_count (unsigned int,unsigned int) ; 

__attribute__((used)) static int queue_setup(struct vb2_queue *q,
			   unsigned int *nbuffers, unsigned int *nplanes,
			   unsigned int sizes[], struct device *alloc_devs[])
{
	struct saa7134_dmaqueue *dmaq = q->drv_priv;
	struct saa7134_dev *dev = dmaq->dev;
	unsigned int size;

	dev->vbi_vlen = dev->tvnorm->vbi_v_stop_0 - dev->tvnorm->vbi_v_start_0 + 1;
	if (dev->vbi_vlen > VBI_LINE_COUNT)
		dev->vbi_vlen = VBI_LINE_COUNT;
	dev->vbi_hlen = VBI_LINE_LENGTH;
	size = dev->vbi_hlen * dev->vbi_vlen * 2;

	*nbuffers = saa7134_buffer_count(size, *nbuffers);
	*nplanes = 1;
	sizes[0] = size;
	return 0;
}