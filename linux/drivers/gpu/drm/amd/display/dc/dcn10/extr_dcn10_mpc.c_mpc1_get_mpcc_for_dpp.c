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
struct mpcc {int dpp_id; struct mpcc* mpcc_bot; } ;
struct mpc_tree {struct mpcc* opp_list; } ;

/* Variables and functions */

struct mpcc *mpc1_get_mpcc_for_dpp(struct mpc_tree *tree, int dpp_id)
{
	struct mpcc *tmp_mpcc = tree->opp_list;

	while (tmp_mpcc != NULL) {
		if (tmp_mpcc->dpp_id == dpp_id)
			return tmp_mpcc;
		tmp_mpcc = tmp_mpcc->mpcc_bot;
	}
	return NULL;
}