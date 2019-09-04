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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  co_cache_error_chain ; 
 int raw_notifier_chain_register (int /*<<< orphan*/ *,struct notifier_block*) ; 

int register_co_cache_error_notifier(struct notifier_block *nb)
{
	return raw_notifier_chain_register(&co_cache_error_chain, nb);
}