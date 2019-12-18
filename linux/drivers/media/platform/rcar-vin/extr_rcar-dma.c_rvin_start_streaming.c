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
struct vb2_queue {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  sizeimage; } ;
struct rvin_dev {int /*<<< orphan*/  scratch_phys; int /*<<< orphan*/  scratch; TYPE_1__ format; int /*<<< orphan*/  dev; int /*<<< orphan*/  qlock; scalar_t__ sequence; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  VB2_BUF_STATE_QUEUED ; 
 int /*<<< orphan*/  dma_alloc_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_all_buffers (struct rvin_dev*,int /*<<< orphan*/ ) ; 
 int rvin_capture_start (struct rvin_dev*) ; 
 int rvin_set_stream (struct rvin_dev*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rvin_dev* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vin_err (struct rvin_dev*,char*) ; 

__attribute__((used)) static int rvin_start_streaming(struct vb2_queue *vq, unsigned int count)
{
	struct rvin_dev *vin = vb2_get_drv_priv(vq);
	unsigned long flags;
	int ret;

	/* Allocate scratch buffer. */
	vin->scratch = dma_alloc_coherent(vin->dev, vin->format.sizeimage,
					  &vin->scratch_phys, GFP_KERNEL);
	if (!vin->scratch) {
		spin_lock_irqsave(&vin->qlock, flags);
		return_all_buffers(vin, VB2_BUF_STATE_QUEUED);
		spin_unlock_irqrestore(&vin->qlock, flags);
		vin_err(vin, "Failed to allocate scratch buffer\n");
		return -ENOMEM;
	}

	ret = rvin_set_stream(vin, 1);
	if (ret) {
		spin_lock_irqsave(&vin->qlock, flags);
		return_all_buffers(vin, VB2_BUF_STATE_QUEUED);
		spin_unlock_irqrestore(&vin->qlock, flags);
		goto out;
	}

	spin_lock_irqsave(&vin->qlock, flags);

	vin->sequence = 0;

	ret = rvin_capture_start(vin);
	if (ret) {
		return_all_buffers(vin, VB2_BUF_STATE_QUEUED);
		rvin_set_stream(vin, 0);
	}

	spin_unlock_irqrestore(&vin->qlock, flags);
out:
	if (ret)
		dma_free_coherent(vin->dev, vin->format.sizeimage, vin->scratch,
				  vin->scratch_phys);

	return ret;
}