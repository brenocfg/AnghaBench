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
struct ath10k_snoc {int /*<<< orphan*/  flags; } ;
struct ath10k {int /*<<< orphan*/  dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_FLAG_CRASH_FLUSH ; 
 int /*<<< orphan*/  ATH10K_SNOC_FLAG_RECOVERY ; 
 int /*<<< orphan*/  ath10k_qmi_wlan_disable (struct ath10k*) ; 
 struct ath10k_snoc* ath10k_snoc_priv (struct ath10k*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_snoc_wlan_disable(struct ath10k *ar)
{
	struct ath10k_snoc *ar_snoc = ath10k_snoc_priv(ar);

	/* If both ATH10K_FLAG_CRASH_FLUSH and ATH10K_SNOC_FLAG_RECOVERY
	 * flags are not set, it means that the driver has restarted
	 * due to a crash inject via debugfs. In this case, the driver
	 * needs to restart the firmware and hence send qmi wlan disable,
	 * during the driver restart sequence.
	 */
	if (!test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags) ||
	    !test_bit(ATH10K_SNOC_FLAG_RECOVERY, &ar_snoc->flags))
		ath10k_qmi_wlan_disable(ar);
}