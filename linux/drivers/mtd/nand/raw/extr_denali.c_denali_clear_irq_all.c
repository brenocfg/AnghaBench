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
struct denali_controller {int nbanks; } ;

/* Variables and functions */
 int /*<<< orphan*/  U32_MAX ; 
 int /*<<< orphan*/  denali_clear_irq (struct denali_controller*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void denali_clear_irq_all(struct denali_controller *denali)
{
	int i;

	for (i = 0; i < denali->nbanks; i++)
		denali_clear_irq(denali, i, U32_MAX);
}