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
struct cvm_mmc_host {scalar_t__ n_minus_one; } ;

/* Variables and functions */
 int /*<<< orphan*/  l2c_unlock_mem_region (scalar_t__,int) ; 

__attribute__((used)) static void octeon_mmc_dmar_fixup_done(struct cvm_mmc_host *host)
{
	if (!host->n_minus_one)
		return;
	l2c_unlock_mem_region(host->n_minus_one, 512);
	host->n_minus_one = 0;
}