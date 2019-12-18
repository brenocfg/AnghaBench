#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int len; int /*<<< orphan*/  cmd; } ;
struct TYPE_5__ {void* sba; TYPE_1__ hdr; } ;
union ism_reg_sba {TYPE_2__ request; } ;
struct ism_sba {int dummy; } ;
struct ism_dev {void* sba_dma_addr; struct ism_sba* sba; TYPE_3__* pdev; } ;
typedef  void* dma_addr_t ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ISM_REG_SBA ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 struct ism_sba* dma_alloc_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct ism_sba*,void*) ; 
 scalar_t__ ism_cmd (struct ism_dev*,union ism_reg_sba*) ; 
 int /*<<< orphan*/  memset (union ism_reg_sba*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int register_sba(struct ism_dev *ism)
{
	union ism_reg_sba cmd;
	dma_addr_t dma_handle;
	struct ism_sba *sba;

	sba = dma_alloc_coherent(&ism->pdev->dev, PAGE_SIZE, &dma_handle,
				 GFP_KERNEL);
	if (!sba)
		return -ENOMEM;

	memset(&cmd, 0, sizeof(cmd));
	cmd.request.hdr.cmd = ISM_REG_SBA;
	cmd.request.hdr.len = sizeof(cmd.request);
	cmd.request.sba = dma_handle;

	if (ism_cmd(ism, &cmd)) {
		dma_free_coherent(&ism->pdev->dev, PAGE_SIZE, sba, dma_handle);
		return -EIO;
	}

	ism->sba = sba;
	ism->sba_dma_addr = dma_handle;

	return 0;
}