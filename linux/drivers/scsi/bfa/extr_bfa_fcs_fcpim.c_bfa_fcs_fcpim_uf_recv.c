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
typedef  int /*<<< orphan*/  u16 ;
struct fchs_s {int type; int /*<<< orphan*/  ox_id; } ;
struct fc_els_cmd_s {int els_code; } ;
struct bfa_fcs_itnim_s {int /*<<< orphan*/  rport; int /*<<< orphan*/  fcs; } ;

/* Variables and functions */
#define  FC_ELS_PRLO 128 
 scalar_t__ FC_TYPE_ELS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fcs_rport_prlo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int) ; 

void
bfa_fcs_fcpim_uf_recv(struct bfa_fcs_itnim_s *itnim,
			struct fchs_s *fchs, u16 len)
{
	struct fc_els_cmd_s *els_cmd;

	bfa_trc(itnim->fcs, fchs->type);

	if (fchs->type != FC_TYPE_ELS)
		return;

	els_cmd = (struct fc_els_cmd_s *) (fchs + 1);

	bfa_trc(itnim->fcs, els_cmd->els_code);

	switch (els_cmd->els_code) {
	case FC_ELS_PRLO:
		bfa_fcs_rport_prlo(itnim->rport, fchs->ox_id);
		break;

	default:
		WARN_ON(1);
	}
}