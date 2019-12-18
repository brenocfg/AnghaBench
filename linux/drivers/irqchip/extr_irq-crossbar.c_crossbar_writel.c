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
struct TYPE_2__ {scalar_t__* register_offsets; scalar_t__ crossbar_base; } ;

/* Variables and functions */
 TYPE_1__* cb ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void crossbar_writel(int irq_no, int cb_no)
{
	writel(cb_no, cb->crossbar_base + cb->register_offsets[irq_no]);
}