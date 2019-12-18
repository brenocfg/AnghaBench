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
struct TYPE_2__ {int /*<<< orphan*/  rnid_atype; } ;
struct fc_lport {int e_d_tov; int r_a_tov; int service_params; int does_npiv; TYPE_1__ rnid_gen; int /*<<< orphan*/  max_rport_retry_count; int /*<<< orphan*/  max_retry_count; scalar_t__ qfull; scalar_t__ link_up; } ;
struct fc_els_rnid_gen {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2FC_MAX_RETRY_CNT ; 
 int /*<<< orphan*/  BNX2FC_MAX_RPORT_RETRY_CNT ; 
 int /*<<< orphan*/  BNX2FC_RNID_HBA ; 
 int ENOMEM ; 
 int FCP_SPPF_CONF_COMPL ; 
 int FCP_SPPF_INIT_FCN ; 
 int FCP_SPPF_RD_XRDY_DIS ; 
 int FCP_SPPF_RETRY ; 
 int /*<<< orphan*/  fc_lport_config (struct fc_lport*) ; 
 scalar_t__ fc_lport_init_stats (struct fc_lport*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int bnx2fc_lport_config(struct fc_lport *lport)
{
	lport->link_up = 0;
	lport->qfull = 0;
	lport->max_retry_count = BNX2FC_MAX_RETRY_CNT;
	lport->max_rport_retry_count = BNX2FC_MAX_RPORT_RETRY_CNT;
	lport->e_d_tov = 2 * 1000;
	lport->r_a_tov = 10 * 1000;

	lport->service_params = (FCP_SPPF_INIT_FCN | FCP_SPPF_RD_XRDY_DIS |
				FCP_SPPF_RETRY | FCP_SPPF_CONF_COMPL);
	lport->does_npiv = 1;

	memset(&lport->rnid_gen, 0, sizeof(struct fc_els_rnid_gen));
	lport->rnid_gen.rnid_atype = BNX2FC_RNID_HBA;

	/* alloc stats structure */
	if (fc_lport_init_stats(lport))
		return -ENOMEM;

	/* Finish fc_lport configuration */
	fc_lport_config(lport);

	return 0;
}