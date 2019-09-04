#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pata_macio_priv {struct macio_dev* mdev; TYPE_2__* dev; int /*<<< orphan*/  node; } ;
struct of_device_id {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_5__ {TYPE_2__ dev; } ;
struct macio_dev {int /*<<< orphan*/  media_bay; TYPE_1__ ofdev; } ;
typedef  int /*<<< orphan*/  resource_size_t ;

/* Variables and functions */
 int EBUSY ; 
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  dev_warn (TYPE_2__*,char*) ; 
 struct pata_macio_priv* devm_kzalloc (TYPE_2__*,int,int /*<<< orphan*/ ) ; 
 unsigned long irq_create_mapping (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lock_media_bay (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  macio_enable_devres (struct macio_dev*) ; 
 unsigned long macio_irq (struct macio_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ macio_irq_count (struct macio_dev*) ; 
 scalar_t__ macio_request_resource (struct macio_dev*,int,char*) ; 
 int macio_resource_count (struct macio_dev*) ; 
 int /*<<< orphan*/  macio_resource_start (struct macio_dev*,int) ; 
 int /*<<< orphan*/  of_node_get (int /*<<< orphan*/ ) ; 
 int pata_macio_common_init (struct pata_macio_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  unlock_media_bay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pata_macio_attach(struct macio_dev *mdev,
			     const struct of_device_id *match)
{
	struct pata_macio_priv	*priv;
	resource_size_t		tfregs, dmaregs = 0;
	unsigned long		irq;
	int			rc;

	/* Check for broken device-trees */
	if (macio_resource_count(mdev) == 0) {
		dev_err(&mdev->ofdev.dev,
			"No addresses for controller\n");
		return -ENXIO;
	}

	/* Enable managed resources */
	macio_enable_devres(mdev);

	/* Allocate and init private data structure */
	priv = devm_kzalloc(&mdev->ofdev.dev,
			    sizeof(struct pata_macio_priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->node = of_node_get(mdev->ofdev.dev.of_node);
	priv->mdev = mdev;
	priv->dev = &mdev->ofdev.dev;

	/* Request memory resource for taskfile registers */
	if (macio_request_resource(mdev, 0, "pata-macio")) {
		dev_err(&mdev->ofdev.dev,
			"Cannot obtain taskfile resource\n");
		return -EBUSY;
	}
	tfregs = macio_resource_start(mdev, 0);

	/* Request resources for DMA registers if any */
	if (macio_resource_count(mdev) >= 2) {
		if (macio_request_resource(mdev, 1, "pata-macio-dma"))
			dev_err(&mdev->ofdev.dev,
				"Cannot obtain DMA resource\n");
		else
			dmaregs = macio_resource_start(mdev, 1);
	}

	/*
	 * Fixup missing IRQ for some old implementations with broken
	 * device-trees.
	 *
	 * This is a bit bogus, it should be fixed in the device-tree itself,
	 * via the existing macio fixups, based on the type of interrupt
	 * controller in the machine. However, I have no test HW for this case,
	 * and this trick works well enough on those old machines...
	 */
	if (macio_irq_count(mdev) == 0) {
		dev_warn(&mdev->ofdev.dev,
			 "No interrupts for controller, using 13\n");
		irq = irq_create_mapping(NULL, 13);
	} else
		irq = macio_irq(mdev, 0);

	/* Prevvent media bay callbacks until fully registered */
	lock_media_bay(priv->mdev->media_bay);

	/* Get register addresses and call common initialization */
	rc = pata_macio_common_init(priv,
				    tfregs,		/* Taskfile regs */
				    dmaregs,		/* DBDMA regs */
				    0,			/* Feature control */
				    irq);
	unlock_media_bay(priv->mdev->media_bay);

	return rc;
}