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
struct memstick_host {int dummy; } ;
struct jmb38x_ms_host {int /*<<< orphan*/  addr; int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct memstick_host*) ; 
 int /*<<< orphan*/  iounmap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memstick_free_host (struct memstick_host*) ; 
 struct jmb38x_ms_host* memstick_priv (struct memstick_host*) ; 

__attribute__((used)) static void jmb38x_ms_free_host(struct memstick_host *msh)
{
	struct jmb38x_ms_host *host = memstick_priv(msh);

	free_irq(host->irq, msh);
	iounmap(host->addr);
	memstick_free_host(msh);
}