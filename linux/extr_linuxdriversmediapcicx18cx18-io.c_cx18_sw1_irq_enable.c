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
typedef  int u32 ;
struct cx18 {int sw1_irq_mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW1_INT_ENABLE_PCI ; 
 int /*<<< orphan*/  SW1_INT_STATUS ; 
 int cx18_read_reg (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_write_reg (struct cx18*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_write_reg_expect (struct cx18*,int,int /*<<< orphan*/ ,int,int) ; 

void cx18_sw1_irq_enable(struct cx18 *cx, u32 val)
{
	cx18_write_reg_expect(cx, val, SW1_INT_STATUS, ~val, val);
	cx->sw1_irq_mask = cx18_read_reg(cx, SW1_INT_ENABLE_PCI) | val;
	cx18_write_reg(cx, cx->sw1_irq_mask, SW1_INT_ENABLE_PCI);
}