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
struct qman_portal {struct qm_portal_config* config; } ;
struct qm_portal_config {int cpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  affine_mask ; 
 int /*<<< orphan*/  affine_mask_lock ; 
 int /*<<< orphan*/  cpumask_clear_cpu (int,int /*<<< orphan*/ *) ; 
 struct qman_portal* get_affine_portal () ; 
 int /*<<< orphan*/  put_affine_portal () ; 
 int /*<<< orphan*/  qman_destroy_portal (struct qman_portal*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

const struct qm_portal_config *qman_destroy_affine_portal(void)
{
	struct qman_portal *qm = get_affine_portal();
	const struct qm_portal_config *pcfg;
	int cpu;

	pcfg = qm->config;
	cpu = pcfg->cpu;

	qman_destroy_portal(qm);

	spin_lock(&affine_mask_lock);
	cpumask_clear_cpu(cpu, &affine_mask);
	spin_unlock(&affine_mask_lock);
	put_affine_portal();
	return pcfg;
}