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
struct ns83820 {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ IER ; 
 scalar_t__ IMR ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void ns83820_disable_interrupts(struct ns83820 *dev)
{
	writel(0, dev->base + IMR);
	writel(0, dev->base + IER);
	readl(dev->base + IER);
}