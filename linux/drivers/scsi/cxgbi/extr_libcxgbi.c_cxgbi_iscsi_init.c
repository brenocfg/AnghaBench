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
struct scsi_transport_template {int dummy; } ;
struct iscsi_transport {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int CXGBI_DBG_ISCSI ; 
 int ENODEV ; 
 struct scsi_transport_template* iscsi_register_transport (struct iscsi_transport*) ; 
 int /*<<< orphan*/  log_debug (int,char*,int /*<<< orphan*/ ,struct scsi_transport_template**) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,struct iscsi_transport*) ; 

int cxgbi_iscsi_init(struct iscsi_transport *itp,
			struct scsi_transport_template **stt)
{
	*stt = iscsi_register_transport(itp);
	if (*stt == NULL) {
		pr_err("unable to register %s transport 0x%p.\n",
			itp->name, itp);
		return -ENODEV;
	}
	log_debug(1 << CXGBI_DBG_ISCSI,
		"%s, registered iscsi transport 0x%p.\n",
		itp->name, stt);
	return 0;
}