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

/* Variables and functions */
 int /*<<< orphan*/  MAPLE_STATE ; 
 int __raw_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int maple_dma_done(void)
{
	return (__raw_readl(MAPLE_STATE) & 1) == 0;
}