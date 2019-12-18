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
struct pcie_link_state {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/ * link_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct pcie_link_state*) ; 

__attribute__((used)) static void free_link_state(struct pcie_link_state *link)
{
	link->pdev->link_state = NULL;
	kfree(link);
}