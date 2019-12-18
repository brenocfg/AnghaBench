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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ath10k_ahb_clock_disable (struct ath10k*) ; 
 int /*<<< orphan*/  ath10k_ahb_halt_chip (struct ath10k*) ; 
 int ath10k_ahb_prepare_device (struct ath10k*) ; 

__attribute__((used)) static int ath10k_ahb_chip_reset(struct ath10k *ar)
{
	int ret;

	ath10k_ahb_halt_chip(ar);
	ath10k_ahb_clock_disable(ar);

	ret = ath10k_ahb_prepare_device(ar);
	if (ret)
		return ret;

	return 0;
}