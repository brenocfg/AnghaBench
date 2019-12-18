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
struct iwl_mvm {scalar_t__ n_nd_channels; int /*<<< orphan*/ * nd_channels; scalar_t__ n_nd_match_sets; int /*<<< orphan*/ * nd_match_sets; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void iwl_mvm_free_nd(struct iwl_mvm *mvm)
{
	kfree(mvm->nd_match_sets);
	mvm->nd_match_sets = NULL;
	mvm->n_nd_match_sets = 0;
	kfree(mvm->nd_channels);
	mvm->nd_channels = NULL;
	mvm->n_nd_channels = 0;
}