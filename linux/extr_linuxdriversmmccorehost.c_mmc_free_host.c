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
struct mmc_host {int /*<<< orphan*/  class_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmc_pwrseq_free (struct mmc_host*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 

void mmc_free_host(struct mmc_host *host)
{
	mmc_pwrseq_free(host);
	put_device(&host->class_dev);
}