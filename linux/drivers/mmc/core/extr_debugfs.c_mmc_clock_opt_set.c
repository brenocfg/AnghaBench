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
typedef  scalar_t__ u64 ;
struct mmc_host {scalar_t__ f_max; scalar_t__ f_min; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  mmc_claim_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_release_host (struct mmc_host*) ; 
 int /*<<< orphan*/  mmc_set_clock (struct mmc_host*,unsigned int) ; 

__attribute__((used)) static int mmc_clock_opt_set(void *data, u64 val)
{
	struct mmc_host *host = data;

	/* We need this check due to input value is u64 */
	if (val != 0 && (val > host->f_max || val < host->f_min))
		return -EINVAL;

	mmc_claim_host(host);
	mmc_set_clock(host, (unsigned int) val);
	mmc_release_host(host);

	return 0;
}