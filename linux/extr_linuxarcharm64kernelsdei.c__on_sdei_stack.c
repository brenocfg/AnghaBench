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
struct stack_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_VMAP_STACK ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 scalar_t__ on_sdei_critical_stack (unsigned long,struct stack_info*) ; 
 scalar_t__ on_sdei_normal_stack (unsigned long,struct stack_info*) ; 

bool _on_sdei_stack(unsigned long sp, struct stack_info *info)
{
	if (!IS_ENABLED(CONFIG_VMAP_STACK))
		return false;

	if (on_sdei_critical_stack(sp, info))
		return true;

	if (on_sdei_normal_stack(sp, info))
		return true;

	return false;
}