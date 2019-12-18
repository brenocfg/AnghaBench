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
struct nvme_ns_ids {int /*<<< orphan*/  nguid; int /*<<< orphan*/  eui64; } ;
struct nvme_id_ns {int /*<<< orphan*/  nguid; int /*<<< orphan*/  eui64; } ;
struct nvme_ctrl {scalar_t__ vs; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 scalar_t__ NVME_VS (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct nvme_ns_ids*,int /*<<< orphan*/ ,int) ; 
 int nvme_identify_ns_descs (struct nvme_ctrl*,unsigned int,struct nvme_ns_ids*) ; 

__attribute__((used)) static int nvme_report_ns_ids(struct nvme_ctrl *ctrl, unsigned int nsid,
		struct nvme_id_ns *id, struct nvme_ns_ids *ids)
{
	int ret = 0;

	memset(ids, 0, sizeof(*ids));

	if (ctrl->vs >= NVME_VS(1, 1, 0))
		memcpy(ids->eui64, id->eui64, sizeof(id->eui64));
	if (ctrl->vs >= NVME_VS(1, 2, 0))
		memcpy(ids->nguid, id->nguid, sizeof(id->nguid));
	if (ctrl->vs >= NVME_VS(1, 3, 0)) {
		 /* Don't treat error as fatal we potentially
		  * already have a NGUID or EUI-64
		  */
		ret = nvme_identify_ns_descs(ctrl, nsid, ids);
		if (ret)
			dev_warn(ctrl->device,
				 "Identify Descriptors failed (%d)\n", ret);
	}
	return ret;
}