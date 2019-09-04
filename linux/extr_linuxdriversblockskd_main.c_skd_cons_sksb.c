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
struct TYPE_2__ {int /*<<< orphan*/ * sksg_list; int /*<<< orphan*/  sksg_dma_address; int /*<<< orphan*/  state; scalar_t__ id; } ;
struct skd_special_context {TYPE_1__ req; int /*<<< orphan*/ * msg_buf; int /*<<< orphan*/  mb_dma_address; int /*<<< orphan*/ * data_buf; int /*<<< orphan*/  db_dma_address; } ;
struct skd_device {int /*<<< orphan*/  msgbuf_cache; int /*<<< orphan*/  databuf_cache; struct skd_special_context internal_skspcl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EINVAL ; 
 int ENOMEM ; 
 int GFP_DMA ; 
 scalar_t__ SKD_ID_INTERNAL ; 
 int /*<<< orphan*/  SKD_REQ_STATE_IDLE ; 
 int __GFP_ZERO ; 
 void* skd_alloc_dma (struct skd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * skd_cons_sg_list (struct skd_device*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skd_format_internal_skspcl (struct skd_device*) ; 

__attribute__((used)) static int skd_cons_sksb(struct skd_device *skdev)
{
	int rc = 0;
	struct skd_special_context *skspcl;

	skspcl = &skdev->internal_skspcl;

	skspcl->req.id = 0 + SKD_ID_INTERNAL;
	skspcl->req.state = SKD_REQ_STATE_IDLE;

	skspcl->data_buf = skd_alloc_dma(skdev, skdev->databuf_cache,
					 &skspcl->db_dma_address,
					 GFP_DMA | __GFP_ZERO,
					 DMA_BIDIRECTIONAL);
	if (skspcl->data_buf == NULL) {
		rc = -ENOMEM;
		goto err_out;
	}

	skspcl->msg_buf = skd_alloc_dma(skdev, skdev->msgbuf_cache,
					&skspcl->mb_dma_address,
					GFP_DMA | __GFP_ZERO, DMA_TO_DEVICE);
	if (skspcl->msg_buf == NULL) {
		rc = -ENOMEM;
		goto err_out;
	}

	skspcl->req.sksg_list = skd_cons_sg_list(skdev, 1,
						 &skspcl->req.sksg_dma_address);
	if (skspcl->req.sksg_list == NULL) {
		rc = -ENOMEM;
		goto err_out;
	}

	if (!skd_format_internal_skspcl(skdev)) {
		rc = -EINVAL;
		goto err_out;
	}

err_out:
	return rc;
}