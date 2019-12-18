#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct pci_dev {int /*<<< orphan*/  dev; } ;
struct megasas_instance {int /*<<< orphan*/  host_device_list_buf_h; scalar_t__ host_device_list_buf; int /*<<< orphan*/  snapdump_prop_h; scalar_t__ snapdump_prop; int /*<<< orphan*/  crash_dump_h; scalar_t__ crash_dump_buf; int /*<<< orphan*/  tgt_prop_h; scalar_t__ tgt_prop; int /*<<< orphan*/  pd_info_h; scalar_t__ pd_info; int /*<<< orphan*/  system_info_h; scalar_t__ system_info_buf; int /*<<< orphan*/  ctrl_info_buf_h; scalar_t__ ctrl_info_buf; int /*<<< orphan*/  ld_targetid_list_buf_h; scalar_t__ ld_targetid_list_buf; int /*<<< orphan*/  ld_list_buf_h; scalar_t__ ld_list_buf; int /*<<< orphan*/  pd_list_buf_h; scalar_t__ pd_list_buf; int /*<<< orphan*/  evt_detail_h; scalar_t__ evt_detail; struct fusion_context* ctrl_context; struct pci_dev* pdev; } ;
struct megasas_evt_detail {int dummy; } ;
struct megasas_ctrl_info {int dummy; } ;
struct fusion_context {int /*<<< orphan*/  ioc_init_request_phys; scalar_t__ ioc_init_request; } ;
struct MR_TARGET_PROPERTIES {int dummy; } ;
struct MR_SNAPDUMP_PROPERTIES {int dummy; } ;
struct MR_PD_LIST {int dummy; } ;
struct MR_PD_INFO {int dummy; } ;
struct MR_LD_TARGETID_LIST {int dummy; } ;
struct MR_LD_LIST {int dummy; } ;
struct MR_DRV_SYSTEM_INFO {int dummy; } ;
struct MPI2_IOC_INIT_REQUEST {int dummy; } ;

/* Variables and functions */
 int CRASH_DMA_BUF_SIZE ; 
 int HOST_DEVICE_LIST_SZ ; 
 int MEGASAS_MAX_PD ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void megasas_free_ctrl_dma_buffers(struct megasas_instance *instance)
{
	struct pci_dev *pdev = instance->pdev;
	struct fusion_context *fusion = instance->ctrl_context;

	if (instance->evt_detail)
		dma_free_coherent(&pdev->dev, sizeof(struct megasas_evt_detail),
				    instance->evt_detail,
				    instance->evt_detail_h);

	if (fusion && fusion->ioc_init_request)
		dma_free_coherent(&pdev->dev,
				  sizeof(struct MPI2_IOC_INIT_REQUEST),
				  fusion->ioc_init_request,
				  fusion->ioc_init_request_phys);

	if (instance->pd_list_buf)
		dma_free_coherent(&pdev->dev,
				    MEGASAS_MAX_PD * sizeof(struct MR_PD_LIST),
				    instance->pd_list_buf,
				    instance->pd_list_buf_h);

	if (instance->ld_list_buf)
		dma_free_coherent(&pdev->dev, sizeof(struct MR_LD_LIST),
				    instance->ld_list_buf,
				    instance->ld_list_buf_h);

	if (instance->ld_targetid_list_buf)
		dma_free_coherent(&pdev->dev, sizeof(struct MR_LD_TARGETID_LIST),
				    instance->ld_targetid_list_buf,
				    instance->ld_targetid_list_buf_h);

	if (instance->ctrl_info_buf)
		dma_free_coherent(&pdev->dev, sizeof(struct megasas_ctrl_info),
				    instance->ctrl_info_buf,
				    instance->ctrl_info_buf_h);

	if (instance->system_info_buf)
		dma_free_coherent(&pdev->dev, sizeof(struct MR_DRV_SYSTEM_INFO),
				    instance->system_info_buf,
				    instance->system_info_h);

	if (instance->pd_info)
		dma_free_coherent(&pdev->dev, sizeof(struct MR_PD_INFO),
				    instance->pd_info, instance->pd_info_h);

	if (instance->tgt_prop)
		dma_free_coherent(&pdev->dev, sizeof(struct MR_TARGET_PROPERTIES),
				    instance->tgt_prop, instance->tgt_prop_h);

	if (instance->crash_dump_buf)
		dma_free_coherent(&pdev->dev, CRASH_DMA_BUF_SIZE,
				    instance->crash_dump_buf,
				    instance->crash_dump_h);

	if (instance->snapdump_prop)
		dma_free_coherent(&pdev->dev,
				  sizeof(struct MR_SNAPDUMP_PROPERTIES),
				  instance->snapdump_prop,
				  instance->snapdump_prop_h);

	if (instance->host_device_list_buf)
		dma_free_coherent(&pdev->dev,
				  HOST_DEVICE_LIST_SZ,
				  instance->host_device_list_buf,
				  instance->host_device_list_buf_h);

}