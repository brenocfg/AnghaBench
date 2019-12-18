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
 int /*<<< orphan*/  iscsi_unregister_transport (struct iscsi_transport*) ; 
 int /*<<< orphan*/  log_debug (int,char*,struct iscsi_transport*,int /*<<< orphan*/ ,struct scsi_transport_template*) ; 

void cxgbi_iscsi_cleanup(struct iscsi_transport *itp,
			struct scsi_transport_template **stt)
{
	if (*stt) {
		log_debug(1 << CXGBI_DBG_ISCSI,
			"de-register transport 0x%p, %s, stt 0x%p.\n",
			itp, itp->name, *stt);
		*stt = NULL;
		iscsi_unregister_transport(itp);
	}
}