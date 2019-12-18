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
struct expansion_card {struct cumanascsi2_info* irq_data; } ;
struct cumanascsi2_info {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALATCH_DIS_INT ; 
 scalar_t__ CUMANASCSI2_ALATCH ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
cumanascsi_2_irqdisable(struct expansion_card *ec, int irqnr)
{
	struct cumanascsi2_info *info = ec->irq_data;
	writeb(ALATCH_DIS_INT, info->base + CUMANASCSI2_ALATCH);
}