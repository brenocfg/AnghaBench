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
struct myrb_ldev_info {int dummy; } ;
struct myrb_hba {int stat_mbox_size; int cmd_mbox_size; int /*<<< orphan*/ * first_cmd_mbox; int /*<<< orphan*/  cmd_mbox_addr; TYPE_1__* pdev; int /*<<< orphan*/ * first_stat_mbox; int /*<<< orphan*/  stat_mbox_addr; int /*<<< orphan*/ * enquiry; int /*<<< orphan*/  enquiry_addr; int /*<<< orphan*/ * err_table; int /*<<< orphan*/  err_table_addr; int /*<<< orphan*/ * ldev_info_buf; int /*<<< orphan*/  ldev_info_addr; } ;
struct myrb_error_entry {int dummy; } ;
struct myrb_enquiry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int MYRB_MAX_CHANNELS ; 
 int MYRB_MAX_LDEVS ; 
 int MYRB_MAX_TARGETS ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void myrb_unmap(struct myrb_hba *cb)
{
	if (cb->ldev_info_buf) {
		size_t ldev_info_size = sizeof(struct myrb_ldev_info) *
			MYRB_MAX_LDEVS;
		dma_free_coherent(&cb->pdev->dev, ldev_info_size,
				  cb->ldev_info_buf, cb->ldev_info_addr);
		cb->ldev_info_buf = NULL;
	}
	if (cb->err_table) {
		size_t err_table_size = sizeof(struct myrb_error_entry) *
			MYRB_MAX_CHANNELS * MYRB_MAX_TARGETS;
		dma_free_coherent(&cb->pdev->dev, err_table_size,
				  cb->err_table, cb->err_table_addr);
		cb->err_table = NULL;
	}
	if (cb->enquiry) {
		dma_free_coherent(&cb->pdev->dev, sizeof(struct myrb_enquiry),
				  cb->enquiry, cb->enquiry_addr);
		cb->enquiry = NULL;
	}
	if (cb->first_stat_mbox) {
		dma_free_coherent(&cb->pdev->dev, cb->stat_mbox_size,
				  cb->first_stat_mbox, cb->stat_mbox_addr);
		cb->first_stat_mbox = NULL;
	}
	if (cb->first_cmd_mbox) {
		dma_free_coherent(&cb->pdev->dev, cb->cmd_mbox_size,
				  cb->first_cmd_mbox, cb->cmd_mbox_addr);
		cb->first_cmd_mbox = NULL;
	}
}