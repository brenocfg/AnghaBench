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
struct mmc_host {int caps; } ;

/* Variables and functions */
 int MMC_CAP_DONE_COMPLETE ; 

__attribute__((used)) static inline bool mmc_host_done_complete(struct mmc_host *host)
{
	return host->caps & MMC_CAP_DONE_COMPLETE;
}