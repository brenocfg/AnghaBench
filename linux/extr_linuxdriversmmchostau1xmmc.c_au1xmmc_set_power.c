#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct au1xmmc_host {int /*<<< orphan*/  mmc; TYPE_1__* platdata; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* set_power ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void au1xmmc_set_power(struct au1xmmc_host *host, int state)
{
	if (host->platdata && host->platdata->set_power)
		host->platdata->set_power(host->mmc, state);
}