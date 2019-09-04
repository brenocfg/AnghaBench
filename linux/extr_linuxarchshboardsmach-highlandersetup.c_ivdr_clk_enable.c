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
struct clk {int dummy; } ;

/* Variables and functions */
 int IVDR_CK_ON ; 
 int /*<<< orphan*/  PA_IVDRCTL ; 
 int __raw_readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ivdr_clk_enable(struct clk *clk)
{
	__raw_writew(__raw_readw(PA_IVDRCTL) | (1 << IVDR_CK_ON), PA_IVDRCTL);
	return 0;
}