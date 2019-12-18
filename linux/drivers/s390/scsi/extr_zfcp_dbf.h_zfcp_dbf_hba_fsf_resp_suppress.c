#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct zfcp_fsf_req {struct fsf_qtcb* qtcb; } ;
struct fcp_resp {scalar_t__ fr_flags; scalar_t__ fr_status; } ;
struct TYPE_12__ {struct fcp_resp resp; } ;
struct TYPE_7__ {TYPE_6__ iu; } ;
struct TYPE_8__ {TYPE_1__ fcp_rsp; } ;
struct TYPE_9__ {TYPE_2__ io; } ;
struct TYPE_11__ {scalar_t__ qtcb_type; } ;
struct TYPE_10__ {scalar_t__ fsf_status; } ;
struct fsf_qtcb {TYPE_3__ bottom; TYPE_5__ prefix; TYPE_4__ header; } ;

/* Variables and functions */
 scalar_t__ FCP_RESID_UNDER ; 
 scalar_t__ FSF_FCP_RSP_AVAILABLE ; 
 scalar_t__ FSF_IO_COMMAND ; 
 scalar_t__ SAM_STAT_GOOD ; 

__attribute__((used)) static inline
bool zfcp_dbf_hba_fsf_resp_suppress(struct zfcp_fsf_req *req)
{
	struct fsf_qtcb *qtcb = req->qtcb;
	u32 fsf_stat = qtcb->header.fsf_status;
	struct fcp_resp *fcp_rsp;
	u8 rsp_flags, fr_status;

	if (qtcb->prefix.qtcb_type != FSF_IO_COMMAND)
		return false; /* not an FCP response */
	fcp_rsp = &qtcb->bottom.io.fcp_rsp.iu.resp;
	rsp_flags = fcp_rsp->fr_flags;
	fr_status = fcp_rsp->fr_status;
	return (fsf_stat == FSF_FCP_RSP_AVAILABLE) &&
		(rsp_flags == FCP_RESID_UNDER) &&
		(fr_status == SAM_STAT_GOOD);
}