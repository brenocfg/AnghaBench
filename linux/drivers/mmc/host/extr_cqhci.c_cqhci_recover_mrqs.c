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
struct cqhci_host {int num_slots; } ;

/* Variables and functions */
 int /*<<< orphan*/  cqhci_recover_mrq (struct cqhci_host*,int) ; 

__attribute__((used)) static void cqhci_recover_mrqs(struct cqhci_host *cq_host)
{
	int i;

	for (i = 0; i < cq_host->num_slots; i++)
		cqhci_recover_mrq(cq_host, i);
}