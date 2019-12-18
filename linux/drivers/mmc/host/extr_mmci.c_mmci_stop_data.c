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
struct mmci_host {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  mmci_set_mask1 (struct mmci_host*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmci_write_datactrlreg (struct mmci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mmci_stop_data(struct mmci_host *host)
{
	mmci_write_datactrlreg(host, 0);
	mmci_set_mask1(host, 0);
	host->data = NULL;
}