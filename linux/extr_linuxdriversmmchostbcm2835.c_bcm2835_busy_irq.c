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
struct bcm2835_host {int use_busy; int /*<<< orphan*/  cmd; } ;

/* Variables and functions */
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  bcm2835_dumpregs (struct bcm2835_host*) ; 
 int /*<<< orphan*/  bcm2835_finish_command (struct bcm2835_host*) ; 

__attribute__((used)) static void bcm2835_busy_irq(struct bcm2835_host *host)
{
	if (WARN_ON(!host->cmd)) {
		bcm2835_dumpregs(host);
		return;
	}

	if (WARN_ON(!host->use_busy)) {
		bcm2835_dumpregs(host);
		return;
	}
	host->use_busy = false;

	bcm2835_finish_command(host);
}