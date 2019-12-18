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
struct si_mode_info {int simr_crt; scalar_t__ simr_rfsd; } ;
struct ucc_tdm_info {struct si_mode_info si_info; } ;
struct ucc_tdm {scalar_t__ tdm_mode; } ;

/* Variables and functions */
 scalar_t__ TDM_INTERNAL_LOOPBACK ; 

__attribute__((used)) static void set_si_param(struct ucc_tdm *utdm, struct ucc_tdm_info *ut_info)
{
	struct si_mode_info *si_info = &ut_info->si_info;

	if (utdm->tdm_mode == TDM_INTERNAL_LOOPBACK) {
		si_info->simr_crt = 1;
		si_info->simr_rfsd = 0;
	}
}