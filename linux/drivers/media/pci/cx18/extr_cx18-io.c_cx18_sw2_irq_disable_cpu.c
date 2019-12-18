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
struct cx18 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW2_INT_ENABLE_CPU ; 
 int cx18_read_reg (struct cx18*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx18_write_reg (struct cx18*,int,int /*<<< orphan*/ ) ; 

void cx18_sw2_irq_disable_cpu(struct cx18 *cx, u32 val)
{
	u32 r;
	r = cx18_read_reg(cx, SW2_INT_ENABLE_CPU);
	cx18_write_reg(cx, r & ~val, SW2_INT_ENABLE_CPU);
}