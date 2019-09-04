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
typedef  int /*<<< orphan*/  u32 ;
struct cqhci_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CQHCI_ISGE ; 
 int /*<<< orphan*/  CQHCI_ISTE ; 
 int /*<<< orphan*/  cqhci_writel (struct cqhci_host*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cqhci_set_irqs(struct cqhci_host *cq_host, u32 set)
{
	cqhci_writel(cq_host, set, CQHCI_ISTE);
	cqhci_writel(cq_host, set, CQHCI_ISGE);
}