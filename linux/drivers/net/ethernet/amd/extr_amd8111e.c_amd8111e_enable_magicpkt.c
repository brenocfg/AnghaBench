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
 scalar_t__ CMD3 ; 
 scalar_t__ CMD7 ; 
 int MPEN_SW ; 
 int MPPLBA ; 
 int VAL0 ; 
 int VAL1 ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int amd8111e_enable_magicpkt(struct amd8111e_priv *lp)
{
	writel( VAL1|MPPLBA, lp->mmio + CMD3);
	writel( VAL0|MPEN_SW, lp->mmio + CMD7);

	/* To eliminate PCI posting bug */
	readl(lp->mmio + CMD7);
	return 0;
}