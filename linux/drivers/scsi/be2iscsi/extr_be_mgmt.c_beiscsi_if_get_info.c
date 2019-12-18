#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {TYPE_1__* pdev; } ;
struct beiscsi_hba {TYPE_2__ ctrl; int /*<<< orphan*/  interface_handle; } ;
struct be_dma_mem {int /*<<< orphan*/  dma; struct be_cmd_get_if_info_req* va; int /*<<< orphan*/  size; } ;
struct be_cmd_resp_hdr {int actual_resp_len; } ;
struct be_cmd_req_hdr {int dummy; } ;
struct be_cmd_get_if_info_resp {int dummy; } ;
struct be_cmd_get_if_info_req {int ip_type; int /*<<< orphan*/  interface_hndl; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_INIT ; 
 int /*<<< orphan*/  CMD_SUBSYSTEM_ISCSI ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  OPCODE_COMMON_ISCSI_NTWK_GET_IF_INFO ; 
 int beiscsi_exec_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ *,struct be_cmd_get_if_info_resp*,int) ; 
 int beiscsi_if_get_handle (struct beiscsi_hba*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int beiscsi_prep_nemb_cmd (struct beiscsi_hba*,struct be_dma_mem*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct be_cmd_get_if_info_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct be_cmd_get_if_info_resp*) ; 
 struct be_cmd_get_if_info_resp* kzalloc (int,int /*<<< orphan*/ ) ; 

int beiscsi_if_get_info(struct beiscsi_hba *phba, int ip_type,
			struct be_cmd_get_if_info_resp **if_info)
{
	struct be_cmd_get_if_info_req *req;
	struct be_dma_mem nonemb_cmd;
	uint32_t ioctl_size = sizeof(struct be_cmd_get_if_info_resp);
	int rc;

	rc = beiscsi_if_get_handle(phba);
	if (rc)
		return rc;

	do {
		rc = beiscsi_prep_nemb_cmd(phba, &nonemb_cmd,
				CMD_SUBSYSTEM_ISCSI,
				OPCODE_COMMON_ISCSI_NTWK_GET_IF_INFO,
				ioctl_size);
		if (rc)
			return rc;

		req = nonemb_cmd.va;
		req->interface_hndl = phba->interface_handle;
		req->ip_type = ip_type;

		/* Allocate memory for if_info */
		*if_info = kzalloc(ioctl_size, GFP_KERNEL);
		if (!*if_info) {
			beiscsi_log(phba, KERN_ERR,
				    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
				    "BG_%d : Memory Allocation Failure\n");

				/* Free the DMA memory for the IOCTL issuing */
				dma_free_coherent(&phba->ctrl.pdev->dev,
						    nonemb_cmd.size,
						    nonemb_cmd.va,
						    nonemb_cmd.dma);
				return -ENOMEM;
		}

		rc =  beiscsi_exec_nemb_cmd(phba, &nonemb_cmd, NULL, *if_info,
					    ioctl_size);

		/* Check if the error is because of Insufficent_Buffer */
		if (rc == -EAGAIN) {

			/* Get the new memory size */
			ioctl_size = ((struct be_cmd_resp_hdr *)
				      nonemb_cmd.va)->actual_resp_len;
			ioctl_size += sizeof(struct be_cmd_req_hdr);

			/* Free the previous allocated DMA memory */
			dma_free_coherent(&phba->ctrl.pdev->dev, nonemb_cmd.size,
					    nonemb_cmd.va,
					    nonemb_cmd.dma);

			/* Free the virtual memory */
			kfree(*if_info);
		} else
			break;
	} while (true);
	return rc;
}