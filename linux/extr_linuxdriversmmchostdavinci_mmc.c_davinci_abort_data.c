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
struct mmc_davinci_host {int dummy; } ;
struct mmc_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_davinci_reset_ctrl (struct mmc_davinci_host*,int) ; 

__attribute__((used)) static void
davinci_abort_data(struct mmc_davinci_host *host, struct mmc_data *data)
{
	mmc_davinci_reset_ctrl(host, 1);
	mmc_davinci_reset_ctrl(host, 0);
}