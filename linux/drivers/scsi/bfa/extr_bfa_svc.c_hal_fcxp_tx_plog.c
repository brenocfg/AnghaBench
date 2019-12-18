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
typedef  scalar_t__ u32 ;
struct fchs_s {int dummy; } ;
struct bfa_s {int /*<<< orphan*/  plog; } ;
struct bfa_fcxp_s {scalar_t__ use_ireqbuf; } ;

/* Variables and functions */
 scalar_t__ BFA_FCXP_REQ_PLD (struct bfa_fcxp_s*) ; 
 int /*<<< orphan*/  BFA_PL_EID_TX ; 
 int /*<<< orphan*/  BFA_PL_MID_HAL_FCXP ; 
 int /*<<< orphan*/  bfa_plog_fchdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct fchs_s*) ; 
 int /*<<< orphan*/  bfa_plog_fchdr_and_pl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct fchs_s*,scalar_t__) ; 

__attribute__((used)) static void
hal_fcxp_tx_plog(struct bfa_s *bfa, u32 reqlen, struct bfa_fcxp_s *fcxp,
		 struct fchs_s *fchs)
{
	/*
	 * TODO: TX ox_id
	 */
	if (reqlen > 0) {
		if (fcxp->use_ireqbuf) {
			u32	pld_w0 =
				*((u32 *) BFA_FCXP_REQ_PLD(fcxp));

			bfa_plog_fchdr_and_pl(bfa->plog, BFA_PL_MID_HAL_FCXP,
					BFA_PL_EID_TX,
					reqlen + sizeof(struct fchs_s), fchs,
					pld_w0);
		} else {
			bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_FCXP,
					BFA_PL_EID_TX,
					reqlen + sizeof(struct fchs_s),
					fchs);
		}
	} else {
		bfa_plog_fchdr(bfa->plog, BFA_PL_MID_HAL_FCXP, BFA_PL_EID_TX,
			       reqlen + sizeof(struct fchs_s), fchs);
	}
}