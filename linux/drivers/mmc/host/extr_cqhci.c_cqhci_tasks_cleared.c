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
struct cqhci_host {int dummy; } ;

/* Variables and functions */
 int CQHCI_CLEAR_ALL_TASKS ; 
 int /*<<< orphan*/  CQHCI_CTL ; 
 int cqhci_readl (struct cqhci_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cqhci_tasks_cleared(struct cqhci_host *cq_host)
{
	return !(cqhci_readl(cq_host, CQHCI_CTL) & CQHCI_CLEAR_ALL_TASKS);
}