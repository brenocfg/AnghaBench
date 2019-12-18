#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  roles; } ;
struct fc_rport_priv {int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  flags; TYPE_1__ ids; struct fc_lport* local_port; } ;
struct fc_lport {int service_params; } ;
struct fc_els_spp {int spp_flags; int /*<<< orphan*/  spp_params; } ;

/* Variables and functions */
 int FCP_SPPF_INIT_FCN ; 
 int FCP_SPPF_RETRY ; 
 int FCP_SPPF_TARG_FCN ; 
 int /*<<< orphan*/  FC_COS_CLASS3 ; 
 int /*<<< orphan*/  FC_RPORT_ROLE_FCP_INITIATOR ; 
 int /*<<< orphan*/  FC_RPORT_ROLE_FCP_TARGET ; 
 int /*<<< orphan*/  FC_RPORT_ROLE_UNKNOWN ; 
 int /*<<< orphan*/  FC_RP_FLAGS_RETRY ; 
 int FC_SPP_EST_IMG_PAIR ; 
 int FC_SPP_RESP_ACK ; 
 int /*<<< orphan*/  htonl (int) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fc_rport_fcp_prli(struct fc_rport_priv *rdata, u32 spp_len,
			     const struct fc_els_spp *rspp,
			     struct fc_els_spp *spp)
{
	struct fc_lport *lport = rdata->local_port;
	u32 fcp_parm;

	fcp_parm = ntohl(rspp->spp_params);
	rdata->ids.roles = FC_RPORT_ROLE_UNKNOWN;
	if (fcp_parm & FCP_SPPF_INIT_FCN)
		rdata->ids.roles |= FC_RPORT_ROLE_FCP_INITIATOR;
	if (fcp_parm & FCP_SPPF_TARG_FCN)
		rdata->ids.roles |= FC_RPORT_ROLE_FCP_TARGET;
	if (fcp_parm & FCP_SPPF_RETRY)
		rdata->flags |= FC_RP_FLAGS_RETRY;
	rdata->supported_classes = FC_COS_CLASS3;

	if (!(lport->service_params & FCP_SPPF_INIT_FCN))
		return 0;

	spp->spp_flags |= rspp->spp_flags & FC_SPP_EST_IMG_PAIR;

	/*
	 * OR in our service parameters with other providers (target), if any.
	 */
	fcp_parm = ntohl(spp->spp_params);
	spp->spp_params = htonl(fcp_parm | lport->service_params);
	return FC_SPP_RESP_ACK;
}