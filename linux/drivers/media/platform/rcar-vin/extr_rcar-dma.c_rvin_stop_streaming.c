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
struct rvin_dev {scalar_t__ state; int /*<<< orphan*/  scratch_phys; int /*<<< orphan*/  scratch; TYPE_1__ format; int /*<<< orphan*/  dev; int /*<<< orphan*/  qlock; } ;

/* Variables and functions */
 int /*<<< orphan*/  RVIN_RETRIES ; 
 int /*<<< orphan*/  RVIN_TIMEOUT_MS ; 
 scalar_t__ STOPPED ; 
 scalar_t__ STOPPING ; 
 int /*<<< orphan*/  VB2_BUF_STATE_ERROR ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  return_all_buffers (struct rvin_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rvin_capture_active (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_capture_stop (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_disable_interrupts (struct rvin_dev*) ; 
 int /*<<< orphan*/  rvin_set_stream (struct rvin_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct rvin_dev* vb2_get_drv_priv (struct vb2_queue*) ; 
 int /*<<< orphan*/  vin_err (struct rvin_dev*,char*) ; 

__attribute__((used)) static void rvin_stop_streaming(struct vb2_queue *vq)
{
	struct rvin_dev *vin = vb2_get_drv_priv(vq);
	unsigned long flags;
	int retries = 0;

	spin_lock_irqsave(&vin->qlock, flags);

	vin->state = STOPPING;

	/* Wait for streaming to stop */
	while (retries++ < RVIN_RETRIES) {

		rvin_capture_stop(vin);

		/* Check if HW is stopped */
		if (!rvin_capture_active(vin)) {
			vin->state = STOPPED;
			break;
		}

		spin_unlock_irqrestore(&vin->qlock, flags);
		msleep(RVIN_TIMEOUT_MS);
		spin_lock_irqsave(&vin->qlock, flags);
	}

	if (vin->state != STOPPED) {
		/*
		 * If this happens something have gone horribly wrong.
		 * Set state to stopped to prevent the interrupt handler
		 * to make things worse...
		 */
		vin_err(vin, "Failed stop HW, something is seriously broken\n");
		vin->state = STOPPED;
	}

	/* Release all active buffers */
	return_all_buffers(vin, VB2_BUF_STATE_ERROR);

	spin_unlock_irqrestore(&vin->qlock, flags);

	rvin_set_stream(vin, 0);

	/* disable interrupts */
	rvin_disable_interrupts(vin);

	/* Free scratch buffer. */
	dma_free_coherent(vin->dev, vin->format.sizeimage, vin->scratch,
			  vin->scratch_phys);
}