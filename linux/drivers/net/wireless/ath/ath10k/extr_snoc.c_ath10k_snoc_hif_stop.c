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
struct ath10k {int /*<<< orphan*/  napi; int /*<<< orphan*/  dev_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int /*<<< orphan*/  ATH10K_FLAG_CRASH_FLUSH ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ath10k_snoc_buffer_cleanup (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_snoc_irq_disable (struct ath10k*) ; 
 int /*<<< orphan*/  napi_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  napi_synchronize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ath10k_snoc_hif_stop(struct ath10k *ar)
{
	if (!test_bit(ATH10K_FLAG_CRASH_FLUSH, &ar->dev_flags))
		ath10k_snoc_irq_disable(ar);

	napi_synchronize(&ar->napi);
	napi_disable(&ar->napi);
	ath10k_snoc_buffer_cleanup(ar);
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot hif stop\n");
}