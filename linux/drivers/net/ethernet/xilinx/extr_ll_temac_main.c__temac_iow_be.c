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
struct temac_local {scalar_t__ regs; } ;

/* Variables and functions */
 void iowrite32be (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void _temac_iow_be(struct temac_local *lp, int offset, u32 value)
{
	return iowrite32be(value, lp->regs + offset);
}