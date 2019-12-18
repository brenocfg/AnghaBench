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
struct nfp_abm {int action_mask; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_ABM_ACT_MARK_DROP ; 

__attribute__((used)) static inline bool nfp_abm_has_mark(struct nfp_abm *abm)
{
	return abm->action_mask & BIT(NFP_ABM_ACT_MARK_DROP);
}