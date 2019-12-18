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
struct megasas_instance {struct pci_dev* pdev; void* crash_dump_buf; void* tgt_prop; void* pd_info; void* system_info_buf; int /*<<< orphan*/  crash_dump_h; int /*<<< orphan*/  tgt_prop_h; int /*<<< orphan*/  pd_info_h; int /*<<< orphan*/  system_info_h; void* ld_targetid_list_buf; int /*<<< orphan*/  ld_targetid_list_buf_h; void* ld_list_buf; int /*<<< orphan*/  ld_list_buf_h; void* ctrl_info_buf; int /*<<< orphan*/  ctrl_info_buf_h; void* pd_list_buf; int /*<<< orphan*/  pd_list_buf_h; void* host_device_list_buf; int /*<<< orphan*/  host_device_list_buf_h; void* snapdump_prop; int /*<<< orphan*/  snapdump_prop_h; void* evt_detail; int /*<<< orphan*/  evt_detail_h; struct fusion_context* ctrl_context; } ;
struct megasas_evt_detail {int dummy; } ;
struct megasas_ctrl_info {int dummy; } ;
struct fusion_context {void* ioc_init_request; int /*<<< orphan*/  ioc_init_request_phys; } ;
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
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HOST_DEVICE_LIST_SZ ; 
 int MEGASAS_MAX_PD ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 void* dma_alloc_coherent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset_devices ; 

__attribute__((used)) static inline
int megasas_alloc_ctrl_dma_buffers(struct megasas_instance *instance)
{
	struct pci_dev *pdev = instance->pdev;
	struct fusion_context *fusion = instance->ctrl_context;

	instance->evt_detail = dma_alloc_coherent(&pdev->dev,
			sizeof(struct megasas_evt_detail),
			&instance->evt_detail_h, GFP_KERNEL);

	if (!instance->evt_detail) {
		dev_err(&instance->pdev->dev,
			"Failed to allocate event detail buffer\n");
		return -ENOMEM;
	}

	if (fusion) {
		fusion->ioc_init_request =
			dma_alloc_coherent(&pdev->dev,
					   sizeof(struct MPI2_IOC_INIT_REQUEST),
					   &fusion->ioc_init_request_phys,
					   GFP_KERNEL);

		if (!fusion->ioc_init_request) {
			dev_err(&pdev->dev,
				"Failed to allocate PD list buffer\n");
			return -ENOMEM;
		}

		instance->snapdump_prop = dma_alloc_coherent(&pdev->dev,
				sizeof(struct MR_SNAPDUMP_PROPERTIES),
				&instance->snapdump_prop_h, GFP_KERNEL);

		if (!instance->snapdump_prop)
			dev_err(&pdev->dev,
				"Failed to allocate snapdump properties buffer\n");

		instance->host_device_list_buf = dma_alloc_coherent(&pdev->dev,
							HOST_DEVICE_LIST_SZ,
							&instance->host_device_list_buf_h,
							GFP_KERNEL);

		if (!instance->host_device_list_buf) {
			dev_err(&pdev->dev,
				"Failed to allocate targetid list buffer\n");
			return -ENOMEM;
		}

	}

	instance->pd_list_buf =
		dma_alloc_coherent(&pdev->dev,
				     MEGASAS_MAX_PD * sizeof(struct MR_PD_LIST),
				     &instance->pd_list_buf_h, GFP_KERNEL);

	if (!instance->pd_list_buf) {
		dev_err(&pdev->dev, "Failed to allocate PD list buffer\n");
		return -ENOMEM;
	}

	instance->ctrl_info_buf =
		dma_alloc_coherent(&pdev->dev,
				     sizeof(struct megasas_ctrl_info),
				     &instance->ctrl_info_buf_h, GFP_KERNEL);

	if (!instance->ctrl_info_buf) {
		dev_err(&pdev->dev,
			"Failed to allocate controller info buffer\n");
		return -ENOMEM;
	}

	instance->ld_list_buf =
		dma_alloc_coherent(&pdev->dev,
				     sizeof(struct MR_LD_LIST),
				     &instance->ld_list_buf_h, GFP_KERNEL);

	if (!instance->ld_list_buf) {
		dev_err(&pdev->dev, "Failed to allocate LD list buffer\n");
		return -ENOMEM;
	}

	instance->ld_targetid_list_buf =
		dma_alloc_coherent(&pdev->dev,
				sizeof(struct MR_LD_TARGETID_LIST),
				&instance->ld_targetid_list_buf_h, GFP_KERNEL);

	if (!instance->ld_targetid_list_buf) {
		dev_err(&pdev->dev,
			"Failed to allocate LD targetid list buffer\n");
		return -ENOMEM;
	}

	if (!reset_devices) {
		instance->system_info_buf =
			dma_alloc_coherent(&pdev->dev,
					sizeof(struct MR_DRV_SYSTEM_INFO),
					&instance->system_info_h, GFP_KERNEL);
		instance->pd_info =
			dma_alloc_coherent(&pdev->dev,
					sizeof(struct MR_PD_INFO),
					&instance->pd_info_h, GFP_KERNEL);
		instance->tgt_prop =
			dma_alloc_coherent(&pdev->dev,
					sizeof(struct MR_TARGET_PROPERTIES),
					&instance->tgt_prop_h, GFP_KERNEL);
		instance->crash_dump_buf =
			dma_alloc_coherent(&pdev->dev, CRASH_DMA_BUF_SIZE,
					&instance->crash_dump_h, GFP_KERNEL);

		if (!instance->system_info_buf)
			dev_err(&instance->pdev->dev,
				"Failed to allocate system info buffer\n");

		if (!instance->pd_info)
			dev_err(&instance->pdev->dev,
				"Failed to allocate pd_info buffer\n");

		if (!instance->tgt_prop)
			dev_err(&instance->pdev->dev,
				"Failed to allocate tgt_prop buffer\n");

		if (!instance->crash_dump_buf)
			dev_err(&instance->pdev->dev,
				"Failed to allocate crash dump buffer\n");
	}

	return 0;
}