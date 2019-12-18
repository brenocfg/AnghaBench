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
typedef  size_t u32 ;
typedef  scalar_t__ u16 ;
struct nvmet_req {int dummy; } ;
struct nvme_ana_rsp_hdr {int /*<<< orphan*/  ngrps; int /*<<< orphan*/  chgcnt; int /*<<< orphan*/  member_0; } ;
struct nvme_ana_group_desc {int /*<<< orphan*/  ngrps; int /*<<< orphan*/  chgcnt; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t NVMET_MAX_ANAGRPS ; 
 int NVMET_MAX_NAMESPACES ; 
 int /*<<< orphan*/  NVME_AEN_BIT_ANA_CHANGE ; 
 scalar_t__ NVME_SC_INTERNAL ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct nvme_ana_rsp_hdr*) ; 
 struct nvme_ana_rsp_hdr* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvmet_ana_chgcnt ; 
 scalar_t__* nvmet_ana_group_enabled ; 
 int /*<<< orphan*/  nvmet_ana_sem ; 
 int /*<<< orphan*/  nvmet_clear_aen_bit (struct nvmet_req*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvmet_copy_to_sgl (struct nvmet_req*,size_t,struct nvme_ana_rsp_hdr*,int) ; 
 size_t nvmet_format_ana_group (struct nvmet_req*,size_t,struct nvme_ana_rsp_hdr*) ; 
 int /*<<< orphan*/  nvmet_req_complete (struct nvmet_req*,scalar_t__) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nvmet_execute_get_log_page_ana(struct nvmet_req *req)
{
	struct nvme_ana_rsp_hdr hdr = { 0, };
	struct nvme_ana_group_desc *desc;
	size_t offset = sizeof(struct nvme_ana_rsp_hdr); /* start beyond hdr */
	size_t len;
	u32 grpid;
	u16 ngrps = 0;
	u16 status;

	status = NVME_SC_INTERNAL;
	desc = kmalloc(sizeof(struct nvme_ana_group_desc) +
			NVMET_MAX_NAMESPACES * sizeof(__le32), GFP_KERNEL);
	if (!desc)
		goto out;

	down_read(&nvmet_ana_sem);
	for (grpid = 1; grpid <= NVMET_MAX_ANAGRPS; grpid++) {
		if (!nvmet_ana_group_enabled[grpid])
			continue;
		len = nvmet_format_ana_group(req, grpid, desc);
		status = nvmet_copy_to_sgl(req, offset, desc, len);
		if (status)
			break;
		offset += len;
		ngrps++;
	}
	for ( ; grpid <= NVMET_MAX_ANAGRPS; grpid++) {
		if (nvmet_ana_group_enabled[grpid])
			ngrps++;
	}

	hdr.chgcnt = cpu_to_le64(nvmet_ana_chgcnt);
	hdr.ngrps = cpu_to_le16(ngrps);
	nvmet_clear_aen_bit(req, NVME_AEN_BIT_ANA_CHANGE);
	up_read(&nvmet_ana_sem);

	kfree(desc);

	/* copy the header last once we know the number of groups */
	status = nvmet_copy_to_sgl(req, 0, &hdr, sizeof(hdr));
out:
	nvmet_req_complete(req, status);
}