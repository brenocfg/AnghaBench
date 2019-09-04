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
struct iolatency_grp {int /*<<< orphan*/  stats; } ;
struct blkg_policy_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_percpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct iolatency_grp*) ; 
 struct iolatency_grp* pd_to_lat (struct blkg_policy_data*) ; 

__attribute__((used)) static void iolatency_pd_free(struct blkg_policy_data *pd)
{
	struct iolatency_grp *iolat = pd_to_lat(pd);
	free_percpu(iolat->stats);
	kfree(iolat);
}