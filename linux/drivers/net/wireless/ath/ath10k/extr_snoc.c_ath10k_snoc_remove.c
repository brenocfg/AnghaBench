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
struct platform_device {int dummy; } ;
struct ath10k_snoc {int /*<<< orphan*/  flags; } ;
struct ath10k {int /*<<< orphan*/  driver_recovery; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_SNOC ; 
 int /*<<< orphan*/  ATH10K_SNOC_FLAG_RECOVERY ; 
 int /*<<< orphan*/  ATH10K_SNOC_FLAG_UNREGISTERING ; 
 int HZ ; 
 int /*<<< orphan*/  ath10k_core_destroy (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_core_unregister (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_hw_power_off (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_qmi_deinit (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_snoc_free_irq (struct ath10k*) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_snoc_release_resource (struct ath10k*) ; 
 struct ath10k* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ath10k_snoc_remove(struct platform_device *pdev)
{
	struct ath10k *ar = platform_get_drvdata(pdev);
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	ath10k_dbg(ar, ATH10K_DBG_SNOC, "snoc remove\n");

	reinit_completion(&ar->driver_recovery);

	if (test_bit(ATH10K_SNOC_FLAG_RECOVERY, &ar_snoc->flags))
		wait_for_completion_timeout(&ar->driver_recovery, 3 * HZ);

	set_bit(ATH10K_SNOC_FLAG_UNREGISTERING, &ar_snoc->flags);

	ath10k_core_unregister(ar);
	ath10k_hw_power_off(ar);
	ath10k_snoc_free_irq(ar);
	ath10k_snoc_release_resource(ar);
	ath10k_qmi_deinit(ar);
	ath10k_core_destroy(ar);

	return 0;
}