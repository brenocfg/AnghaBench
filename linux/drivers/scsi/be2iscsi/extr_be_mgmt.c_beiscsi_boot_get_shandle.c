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
struct beiscsi_hba {int dummy; } ;
struct be_mcc_wrb {int dummy; } ;
struct be_cmd_get_boot_target_resp {unsigned int boot_session_handle; int /*<<< orphan*/  boot_session_count; } ;

/* Variables and functions */
 int BEISCSI_LOG_CONFIG ; 
 int BEISCSI_LOG_INIT ; 
 unsigned int BE_BOOT_INVALID_SHANDLE ; 
 int EAGAIN ; 
 int EBUSY ; 
 int ENXIO ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 unsigned int __beiscsi_boot_get_shandle (struct beiscsi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  beiscsi_log (struct beiscsi_hba*,int /*<<< orphan*/ ,int,char*) ; 
 int beiscsi_mccq_compl_wait (struct beiscsi_hba*,unsigned int,struct be_mcc_wrb**,int /*<<< orphan*/ *) ; 
 struct be_cmd_get_boot_target_resp* embedded_payload (struct be_mcc_wrb*) ; 

int beiscsi_boot_get_shandle(struct beiscsi_hba *phba, unsigned int *s_handle)
{
	struct be_cmd_get_boot_target_resp *boot_resp;
	struct be_mcc_wrb *wrb;
	unsigned int tag;
	int rc;

	*s_handle = BE_BOOT_INVALID_SHANDLE;
	/* get configured boot session count and handle */
	tag = __beiscsi_boot_get_shandle(phba, 0);
	if (!tag) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_CONFIG | BEISCSI_LOG_INIT,
			    "BG_%d : Getting Boot Target Info Failed\n");
		return -EAGAIN;
	}

	rc = beiscsi_mccq_compl_wait(phba, tag, &wrb, NULL);
	if (rc) {
		beiscsi_log(phba, KERN_ERR,
			    BEISCSI_LOG_INIT | BEISCSI_LOG_CONFIG,
			    "BG_%d : MBX CMD get_boot_target Failed\n");
		return -EBUSY;
	}

	boot_resp = embedded_payload(wrb);
	/* check if there are any boot targets configured */
	if (!boot_resp->boot_session_count) {
		__beiscsi_log(phba, KERN_INFO,
			      "BG_%d : No boot targets configured\n");
		return -ENXIO;
	}

	/* only if FW has logged in to the boot target, s_handle is valid */
	*s_handle = boot_resp->boot_session_handle;
	return 1;
}