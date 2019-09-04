#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  va; } ;
struct mic_device {int dp_dma_addr; int /*<<< orphan*/  dma_mbdev; int /*<<< orphan*/  scdev; int /*<<< orphan*/  vpdev; TYPE_3__* ops; TYPE_2__* intr_ops; int /*<<< orphan*/ * dma_ch; int /*<<< orphan*/  aper; TYPE_1__* pdev; int /*<<< orphan*/  num_dma_ch; int /*<<< orphan*/  dp; TYPE_4__ mmio; } ;
struct cosm_device {int dummy; } ;
struct TYPE_7__ {int (* load_mic_fw ) (struct mic_device*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* send_firmware_intr ) (struct mic_device*) ;int /*<<< orphan*/  (* write_spad ) (struct mic_device*,int /*<<< orphan*/ ,int) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  (* enable_interrupts ) (struct mic_device*) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBUS_DEV_DMA_HOST ; 
 int /*<<< orphan*/  MIC_DPHI_SPAD ; 
 int /*<<< orphan*/  MIC_DPLO_SPAD ; 
 int /*<<< orphan*/  MIC_SCIF_DEV ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOP_DEV_TRNSP ; 
 int /*<<< orphan*/  __mic_dma_ops ; 
 int /*<<< orphan*/  _mic_dma_ops ; 
 struct mic_device* cosmdev_to_mdev (struct cosm_device*) ; 
 int /*<<< orphan*/  mbus_hw_ops ; 
 int /*<<< orphan*/  mbus_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbus_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mic_bootparam_init (struct mic_device*) ; 
 int /*<<< orphan*/  mic_dma_ops ; 
 int /*<<< orphan*/  mic_free_dma_chans (struct mic_device*) ; 
 int /*<<< orphan*/  mic_intr_restore (struct mic_device*) ; 
 int /*<<< orphan*/  mic_request_dma_chans (struct mic_device*) ; 
 int /*<<< orphan*/  mic_smpt_restore (struct mic_device*) ; 
 int /*<<< orphan*/  scif_hw_ops ; 
 int /*<<< orphan*/  scif_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  scif_unregister_device (int /*<<< orphan*/ ) ; 
 int stub1 (struct mic_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct mic_device*) ; 
 int /*<<< orphan*/  stub3 (struct mic_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct mic_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct mic_device*) ; 
 int /*<<< orphan*/  vop_hw_ops ; 
 int /*<<< orphan*/  vop_register_device (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vop_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _mic_start(struct cosm_device *cdev, int id)
{
	struct mic_device *mdev = cosmdev_to_mdev(cdev);
	int rc;

	mic_bootparam_init(mdev);
	mdev->dma_mbdev = mbus_register_device(&mdev->pdev->dev,
					       MBUS_DEV_DMA_HOST, &mic_dma_ops,
					       &mbus_hw_ops, id, mdev->mmio.va);
	if (IS_ERR(mdev->dma_mbdev)) {
		rc = PTR_ERR(mdev->dma_mbdev);
		goto unlock_ret;
	}
	if (!mic_request_dma_chans(mdev)) {
		rc = -ENODEV;
		goto dma_remove;
	}
	mdev->scdev = scif_register_device(&mdev->pdev->dev, MIC_SCIF_DEV,
					   &__mic_dma_ops, &scif_hw_ops,
					   id + 1, 0, &mdev->mmio,
					   &mdev->aper, mdev->dp, NULL,
					   mdev->dma_ch, mdev->num_dma_ch,
					   true);
	if (IS_ERR(mdev->scdev)) {
		rc = PTR_ERR(mdev->scdev);
		goto dma_free;
	}

	mdev->vpdev = vop_register_device(&mdev->pdev->dev,
					  VOP_DEV_TRNSP, &_mic_dma_ops,
					  &vop_hw_ops, id + 1, &mdev->aper,
					  mdev->dma_ch[0]);
	if (IS_ERR(mdev->vpdev)) {
		rc = PTR_ERR(mdev->vpdev);
		goto scif_remove;
	}

	rc = mdev->ops->load_mic_fw(mdev, NULL);
	if (rc)
		goto vop_remove;
	mic_smpt_restore(mdev);
	mic_intr_restore(mdev);
	mdev->intr_ops->enable_interrupts(mdev);
	mdev->ops->write_spad(mdev, MIC_DPLO_SPAD, mdev->dp_dma_addr);
	mdev->ops->write_spad(mdev, MIC_DPHI_SPAD, mdev->dp_dma_addr >> 32);
	mdev->ops->send_firmware_intr(mdev);
	goto unlock_ret;
vop_remove:
	vop_unregister_device(mdev->vpdev);
scif_remove:
	scif_unregister_device(mdev->scdev);
dma_free:
	mic_free_dma_chans(mdev);
dma_remove:
	mbus_unregister_device(mdev->dma_mbdev);
unlock_ret:
	return rc;
}