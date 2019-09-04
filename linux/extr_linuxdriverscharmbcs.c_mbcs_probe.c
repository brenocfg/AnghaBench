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
struct mbcs_soft {int /*<<< orphan*/  algo; int /*<<< orphan*/  putdma; int /*<<< orphan*/  getdma; int /*<<< orphan*/  algolock; int /*<<< orphan*/  dmareadlock; int /*<<< orphan*/  dmawritelock; int /*<<< orphan*/  algo_queue; int /*<<< orphan*/  dmaread_queue; int /*<<< orphan*/  dmawrite_queue; struct cx_dev* cxdev; void* mmr_base; int /*<<< orphan*/  list; int /*<<< orphan*/  nasid; } ;
struct cx_device_id {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nasid; } ;
struct cx_dev {int /*<<< orphan*/  dev; struct mbcs_soft* soft; TYPE_1__ cx_id; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_attr_algo ; 
 int /*<<< orphan*/  device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct mbcs_soft* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbcs_algo_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbcs_getdma_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mbcs_hw_init (struct mbcs_soft*) ; 
 int /*<<< orphan*/  mbcs_intr_alloc (struct cx_dev*) ; 
 int /*<<< orphan*/  mbcs_putdma_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  soft_list ; 
 scalar_t__ tiocx_swin_base (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mbcs_probe(struct cx_dev *dev, const struct cx_device_id *id)
{
	struct mbcs_soft *soft;

	dev->soft = NULL;

	soft = kzalloc(sizeof(struct mbcs_soft), GFP_KERNEL);
	if (soft == NULL)
		return -ENOMEM;

	soft->nasid = dev->cx_id.nasid;
	list_add(&soft->list, &soft_list);
	soft->mmr_base = (void *)tiocx_swin_base(dev->cx_id.nasid);
	dev->soft = soft;
	soft->cxdev = dev;

	init_waitqueue_head(&soft->dmawrite_queue);
	init_waitqueue_head(&soft->dmaread_queue);
	init_waitqueue_head(&soft->algo_queue);

	mutex_init(&soft->dmawritelock);
	mutex_init(&soft->dmareadlock);
	mutex_init(&soft->algolock);

	mbcs_getdma_init(&soft->getdma);
	mbcs_putdma_init(&soft->putdma);
	mbcs_algo_init(&soft->algo);

	mbcs_hw_init(soft);

	/* Allocate interrupts */
	mbcs_intr_alloc(dev);

	device_create_file(&dev->dev, &dev_attr_algo);

	return 0;
}