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
typedef  void* wwn_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct bfa_lps_s {int /*<<< orphan*/  auth_en; int /*<<< orphan*/  fdisc; void* nwwn; void* pwwn; int /*<<< orphan*/  pdusz; int /*<<< orphan*/  alpa; void* uarg; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 int /*<<< orphan*/  BFA_LPS_SM_LOGIN ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 

void
bfa_lps_flogi(struct bfa_lps_s *lps, void *uarg, u8 alpa, u16 pdusz,
	wwn_t pwwn, wwn_t nwwn, bfa_boolean_t auth_en)
{
	lps->uarg	= uarg;
	lps->alpa	= alpa;
	lps->pdusz	= pdusz;
	lps->pwwn	= pwwn;
	lps->nwwn	= nwwn;
	lps->fdisc	= BFA_FALSE;
	lps->auth_en	= auth_en;
	bfa_sm_send_event(lps, BFA_LPS_SM_LOGIN);
}