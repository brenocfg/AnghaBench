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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mdp5_kms {int num_intfs; int /*<<< orphan*/  glob_state_lock; int /*<<< orphan*/  glob_state; scalar_t__ rpm_enabled; int /*<<< orphan*/ * intfs; scalar_t__ cfg; scalar_t__ smp; scalar_t__ ctlm; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_atomic_private_obj_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_lock_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_cfg_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mdp5_ctlm_destroy (scalar_t__) ; 
 int /*<<< orphan*/  mdp5_smp_destroy (scalar_t__) ; 
 struct mdp5_kms* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  pm_runtime_disable (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mdp5_destroy(struct platform_device *pdev)
{
	struct mdp5_kms *mdp5_kms = platform_get_drvdata(pdev);
	int i;

	if (mdp5_kms->ctlm)
		mdp5_ctlm_destroy(mdp5_kms->ctlm);
	if (mdp5_kms->smp)
		mdp5_smp_destroy(mdp5_kms->smp);
	if (mdp5_kms->cfg)
		mdp5_cfg_destroy(mdp5_kms->cfg);

	for (i = 0; i < mdp5_kms->num_intfs; i++)
		kfree(mdp5_kms->intfs[i]);

	if (mdp5_kms->rpm_enabled)
		pm_runtime_disable(&pdev->dev);

	drm_atomic_private_obj_fini(&mdp5_kms->glob_state);
	drm_modeset_lock_fini(&mdp5_kms->glob_state_lock);
}