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
struct TYPE_2__ {scalar_t__ error; } ;
struct mmci_host {TYPE_1__ stop_abort; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmci_start_command (struct mmci_host*,TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmci_stop_command(struct mmci_host *host)
{
	host->stop_abort.error = 0;
	mmci_start_command(host, &host->stop_abort, 0);
}