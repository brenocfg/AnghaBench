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
struct lpfc_vport {scalar_t__ cfg_enable_fc4_type; scalar_t__ gidft_inp; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  FC_TYPE_NVME ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ LPFC_ENABLE_BOTH ; 
 scalar_t__ LPFC_ENABLE_FCP ; 
 scalar_t__ LPFC_ENABLE_NVME ; 
 int /*<<< orphan*/  SLI_CTNS_GID_FT ; 
 int /*<<< orphan*/  SLI_CTPT_FCP ; 
 int /*<<< orphan*/  SLI_CTPT_NVME ; 
 scalar_t__ lpfc_ns_cmd (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,char*,...) ; 

int
lpfc_issue_gidft(struct lpfc_vport *vport)
{
	/* Good status, issue CT Request to NameServer */
	if ((vport->cfg_enable_fc4_type == LPFC_ENABLE_BOTH) ||
	    (vport->cfg_enable_fc4_type == LPFC_ENABLE_FCP)) {
		if (lpfc_ns_cmd(vport, SLI_CTNS_GID_FT, 0, SLI_CTPT_FCP)) {
			/* Cannot issue NameServer FCP Query, so finish up
			 * discovery
			 */
			lpfc_printf_vlog(vport, KERN_ERR, LOG_SLI,
					 "0604 %s FC TYPE %x %s\n",
					 "Failed to issue GID_FT to ",
					 FC_TYPE_FCP,
					 "Finishing discovery.");
			return 0;
		}
		vport->gidft_inp++;
	}

	if ((vport->cfg_enable_fc4_type == LPFC_ENABLE_BOTH) ||
	    (vport->cfg_enable_fc4_type == LPFC_ENABLE_NVME)) {
		if (lpfc_ns_cmd(vport, SLI_CTNS_GID_FT, 0, SLI_CTPT_NVME)) {
			/* Cannot issue NameServer NVME Query, so finish up
			 * discovery
			 */
			lpfc_printf_vlog(vport, KERN_ERR, LOG_SLI,
					 "0605 %s FC_TYPE %x %s %d\n",
					 "Failed to issue GID_FT to ",
					 FC_TYPE_NVME,
					 "Finishing discovery: gidftinp ",
					 vport->gidft_inp);
			if (vport->gidft_inp == 0)
				return 0;
		} else
			vport->gidft_inp++;
	}
	return vport->gidft_inp;
}