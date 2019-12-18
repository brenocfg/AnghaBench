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
struct fc_lport {int max_retry_count; int max_rport_retry_count; int service_params; int does_npiv; scalar_t__ lso_max; scalar_t__ lro_xid; scalar_t__ lro_enabled; scalar_t__ seq_offload; scalar_t__ crc_offload; int /*<<< orphan*/  r_a_tov; int /*<<< orphan*/  e_d_tov; scalar_t__ qfull; scalar_t__ link_up; } ;

/* Variables and functions */
 int FCP_SPPF_CONF_COMPL ; 
 int FCP_SPPF_INIT_FCN ; 
 int FCP_SPPF_RD_XRDY_DIS ; 
 int FCP_SPPF_RETRY ; 
 int /*<<< orphan*/  fc_lport_config (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_init_stats (struct fc_lport*) ; 
 int /*<<< orphan*/  fcoe_e_d_tov ; 
 int /*<<< orphan*/  fcoe_r_a_tov ; 

__attribute__((used)) static int fcoe_lport_config(struct fc_lport *lport)
{
	lport->link_up = 0;
	lport->qfull = 0;
	lport->max_retry_count = 3;
	lport->max_rport_retry_count = 3;
	lport->e_d_tov = fcoe_e_d_tov;
	lport->r_a_tov = fcoe_r_a_tov;
	lport->service_params = (FCP_SPPF_INIT_FCN | FCP_SPPF_RD_XRDY_DIS |
				 FCP_SPPF_RETRY | FCP_SPPF_CONF_COMPL);
	lport->does_npiv = 1;

	fc_lport_init_stats(lport);

	/* lport fc_lport related configuration */
	fc_lport_config(lport);

	/* offload related configuration */
	lport->crc_offload = 0;
	lport->seq_offload = 0;
	lport->lro_enabled = 0;
	lport->lro_xid = 0;
	lport->lso_max = 0;

	return 0;
}