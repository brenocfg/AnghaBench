#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cgroup_subsys_state {int dummy; } ;
struct blkcg {scalar_t__* cpd; int /*<<< orphan*/  all_blkcgs_node; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* cpd_free_fn ) (scalar_t__) ;} ;

/* Variables and functions */
 int BLKCG_MAX_POLS ; 
 int /*<<< orphan*/  blkcg_pol_mutex ; 
 TYPE_1__** blkcg_policy ; 
 struct blkcg* css_to_blkcg (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  kfree (struct blkcg*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void blkcg_css_free(struct cgroup_subsys_state *css)
{
	struct blkcg *blkcg = css_to_blkcg(css);
	int i;

	mutex_lock(&blkcg_pol_mutex);

	list_del(&blkcg->all_blkcgs_node);

	for (i = 0; i < BLKCG_MAX_POLS; i++)
		if (blkcg->cpd[i])
			blkcg_policy[i]->cpd_free_fn(blkcg->cpd[i]);

	mutex_unlock(&blkcg_pol_mutex);

	kfree(blkcg);
}