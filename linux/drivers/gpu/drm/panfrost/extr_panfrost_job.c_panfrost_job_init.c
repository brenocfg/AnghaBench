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
struct panfrost_job_slot {TYPE_1__* queue; int /*<<< orphan*/  job_lock; } ;
struct panfrost_device {int /*<<< orphan*/  dev; struct panfrost_job_slot* js; } ;
struct TYPE_2__ {int /*<<< orphan*/  sched; int /*<<< orphan*/  fence_context; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int NUM_JOB_SLOTS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct panfrost_job_slot* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct panfrost_device*) ; 
 int /*<<< orphan*/  dma_fence_context_alloc (int) ; 
 int /*<<< orphan*/  drm_sched_fini (int /*<<< orphan*/ *) ; 
 int drm_sched_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  panfrost_job_enable_interrupts (struct panfrost_device*) ; 
 int /*<<< orphan*/  panfrost_job_irq_handler ; 
 int /*<<< orphan*/  panfrost_sched_ops ; 
 int platform_get_irq_byname (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_platform_device (int /*<<< orphan*/ ) ; 

int panfrost_job_init(struct panfrost_device *pfdev)
{
	struct panfrost_job_slot *js;
	int ret, j, irq;

	pfdev->js = js = devm_kzalloc(pfdev->dev, sizeof(*js), GFP_KERNEL);
	if (!js)
		return -ENOMEM;

	spin_lock_init(&js->job_lock);

	irq = platform_get_irq_byname(to_platform_device(pfdev->dev), "job");
	if (irq <= 0)
		return -ENODEV;

	ret = devm_request_irq(pfdev->dev, irq, panfrost_job_irq_handler,
			       IRQF_SHARED, "job", pfdev);
	if (ret) {
		dev_err(pfdev->dev, "failed to request job irq");
		return ret;
	}

	for (j = 0; j < NUM_JOB_SLOTS; j++) {
		js->queue[j].fence_context = dma_fence_context_alloc(1);

		ret = drm_sched_init(&js->queue[j].sched,
				     &panfrost_sched_ops,
				     1, 0, msecs_to_jiffies(500),
				     "pan_js");
		if (ret) {
			dev_err(pfdev->dev, "Failed to create scheduler: %d.", ret);
			goto err_sched;
		}
	}

	panfrost_job_enable_interrupts(pfdev);

	return 0;

err_sched:
	for (j--; j >= 0; j--)
		drm_sched_fini(&js->queue[j].sched);

	return ret;
}