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
struct mmc_host {int hold_retune; scalar_t__ retune_now; } ;

/* Variables and functions */

__attribute__((used)) static inline void mmc_retune_hold_now(struct mmc_host *host)
{
	host->retune_now = 0;
	host->hold_retune += 1;
}