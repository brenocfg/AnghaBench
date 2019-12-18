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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct bfa_s {int dummy; } ;
struct bfa_lps_s {scalar_t__ lp_pid; int /*<<< orphan*/  bfa_tag; } ;
struct bfa_lps_mod_s {int num_lps; struct bfa_lps_s* lps_arr; } ;

/* Variables and functions */
 struct bfa_lps_mod_s* BFA_LPS_MOD (struct bfa_s*) ; 

u8
bfa_lps_get_tag_from_pid(struct bfa_s *bfa, u32 pid)
{
	struct bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	struct bfa_lps_s	*lps;
	int			i;

	for (i = 0, lps = mod->lps_arr; i < mod->num_lps; i++, lps++) {
		if (lps->lp_pid == pid)
			return lps->bfa_tag;
	}

	/* Return base port tag anyway */
	return 0;
}