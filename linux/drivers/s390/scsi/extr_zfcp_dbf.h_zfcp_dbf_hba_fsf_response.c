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
struct zfcp_fsf_req {int status; struct fsf_qtcb* qtcb; } ;
struct TYPE_4__ {scalar_t__ fsf_status; scalar_t__ fsf_command; scalar_t__ log_length; } ;
struct TYPE_3__ {scalar_t__ prot_status; } ;
struct fsf_qtcb {TYPE_2__ header; TYPE_1__ prefix; } ;

/* Variables and functions */
 scalar_t__ FSF_GOOD ; 
 scalar_t__ FSF_PROT_FSF_STATUS_PRESENTED ; 
 scalar_t__ FSF_PROT_GOOD ; 
 scalar_t__ FSF_QTCB_OPEN_LUN ; 
 scalar_t__ FSF_QTCB_OPEN_PORT_WITH_DID ; 
 int ZFCP_STATUS_FSFREQ_DISMISSED ; 
 int ZFCP_STATUS_FSFREQ_ERROR ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  zfcp_dbf_hba_fsf_resp (char*,int,struct zfcp_fsf_req*) ; 
 scalar_t__ zfcp_dbf_hba_fsf_resp_suppress (struct zfcp_fsf_req*) ; 

__attribute__((used)) static inline
void zfcp_dbf_hba_fsf_response(struct zfcp_fsf_req *req)
{
	struct fsf_qtcb *qtcb = req->qtcb;

	if (unlikely(req->status & (ZFCP_STATUS_FSFREQ_DISMISSED |
				    ZFCP_STATUS_FSFREQ_ERROR))) {
		zfcp_dbf_hba_fsf_resp("fs_rerr", 3, req);

	} else if ((qtcb->prefix.prot_status != FSF_PROT_GOOD) &&
	    (qtcb->prefix.prot_status != FSF_PROT_FSF_STATUS_PRESENTED)) {
		zfcp_dbf_hba_fsf_resp("fs_perr", 1, req);

	} else if (qtcb->header.fsf_status != FSF_GOOD) {
		zfcp_dbf_hba_fsf_resp("fs_ferr",
				      zfcp_dbf_hba_fsf_resp_suppress(req)
				      ? 5 : 1, req);

	} else if ((qtcb->header.fsf_command == FSF_QTCB_OPEN_PORT_WITH_DID) ||
		   (qtcb->header.fsf_command == FSF_QTCB_OPEN_LUN)) {
		zfcp_dbf_hba_fsf_resp("fs_open", 4, req);

	} else if (qtcb->header.log_length) {
		zfcp_dbf_hba_fsf_resp("fs_qtcb", 5, req);

	} else {
		zfcp_dbf_hba_fsf_resp("fs_norm", 6, req);
	}
}