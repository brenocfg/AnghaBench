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
struct rdma_cm_id {int dummy; } ;
struct nvme_rdma_cm_rej {void* sts; void* recfmt; } ;
typedef  int /*<<< orphan*/  rej ;
typedef  enum nvme_rdma_cm_status { ____Placeholder_nvme_rdma_cm_status } nvme_rdma_cm_status ;

/* Variables and functions */
 int NVME_RDMA_CM_FMT_1_0 ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  nvme_rdma_cm_msg (int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int /*<<< orphan*/ ) ; 
 int rdma_reject (struct rdma_cm_id*,void*,int) ; 

__attribute__((used)) static int nvmet_rdma_cm_reject(struct rdma_cm_id *cm_id,
				enum nvme_rdma_cm_status status)
{
	struct nvme_rdma_cm_rej rej;

	pr_debug("rejecting connect request: status %d (%s)\n",
		 status, nvme_rdma_cm_msg(status));

	rej.recfmt = cpu_to_le16(NVME_RDMA_CM_FMT_1_0);
	rej.sts = cpu_to_le16(status);

	return rdma_reject(cm_id, (void *)&rej, sizeof(rej));
}