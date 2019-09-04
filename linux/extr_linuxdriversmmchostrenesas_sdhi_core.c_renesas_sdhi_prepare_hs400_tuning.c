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
struct tmio_mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  host_to_priv (struct tmio_mmc_host*) ; 
 int /*<<< orphan*/  renesas_sdhi_reset_hs400_mode (struct tmio_mmc_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void renesas_sdhi_prepare_hs400_tuning(struct tmio_mmc_host *host)
{
	renesas_sdhi_reset_hs400_mode(host, host_to_priv(host));
}