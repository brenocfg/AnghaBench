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
struct TYPE_2__ {scalar_t__ sksg_dma_address; int /*<<< orphan*/ * sksg_list; } ;
struct skd_special_context {TYPE_1__ req; scalar_t__ mb_dma_address; int /*<<< orphan*/ * msg_buf; scalar_t__ db_dma_address; int /*<<< orphan*/ * data_buf; } ;
struct skd_device {int /*<<< orphan*/  msgbuf_cache; int /*<<< orphan*/  databuf_cache; struct skd_special_context internal_skspcl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int /*<<< orphan*/  skd_free_dma (struct skd_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skd_free_sg_list (struct skd_device*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void skd_free_sksb(struct skd_device *skdev)
{
	struct skd_special_context *skspcl = &skdev->internal_skspcl;

	skd_free_dma(skdev, skdev->databuf_cache, skspcl->data_buf,
		     skspcl->db_dma_address, DMA_BIDIRECTIONAL);

	skspcl->data_buf = NULL;
	skspcl->db_dma_address = 0;

	skd_free_dma(skdev, skdev->msgbuf_cache, skspcl->msg_buf,
		     skspcl->mb_dma_address, DMA_TO_DEVICE);

	skspcl->msg_buf = NULL;
	skspcl->mb_dma_address = 0;

	skd_free_sg_list(skdev, skspcl->req.sksg_list,
			 skspcl->req.sksg_dma_address);

	skspcl->req.sksg_list = NULL;
	skspcl->req.sksg_dma_address = 0;
}