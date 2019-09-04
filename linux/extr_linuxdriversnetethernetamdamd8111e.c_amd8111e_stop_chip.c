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
struct amd8111e_priv {scalar_t__ mmio; } ;

/* Variables and functions */
 scalar_t__ CMD0 ; 
 int /*<<< orphan*/  RUN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void amd8111e_stop_chip(struct amd8111e_priv *lp)
{
	writel(RUN, lp->mmio + CMD0);

	/* To avoid PCI posting bug */
	readl(lp->mmio + CMD0);
}