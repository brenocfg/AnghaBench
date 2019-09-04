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
 int /*<<< orphan*/  APU ; 
 int /*<<< orphan*/  CPU ; 
 int IRQ_APU_TO_EPU ; 
 int IRQ_CPU_TO_EPU ; 
 int /*<<< orphan*/  cx18_api_epu_cmd_irq (struct cx18*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void epu_cmd(struct cx18 *cx, u32 sw1)
{
	if (sw1 & IRQ_CPU_TO_EPU)
		cx18_api_epu_cmd_irq(cx, CPU);
	if (sw1 & IRQ_APU_TO_EPU)
		cx18_api_epu_cmd_irq(cx, APU);
}