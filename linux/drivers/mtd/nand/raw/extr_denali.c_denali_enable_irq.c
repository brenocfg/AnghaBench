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
struct denali_controller {int nbanks; scalar_t__ reg; } ;

/* Variables and functions */
 scalar_t__ GLOBAL_INT_ENABLE ; 
 int /*<<< orphan*/  GLOBAL_INT_EN_FLAG ; 
 scalar_t__ INTR_EN (int) ; 
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  iowrite32 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void denali_enable_irq(struct denali_controller *denali)
{
	int i;

	for (i = 0; i < denali->nbanks; i++)
		iowrite32(U32_MAX, denali->reg + INTR_EN(i));
	iowrite32(GLOBAL_INT_EN_FLAG, denali->reg + GLOBAL_INT_ENABLE);
}