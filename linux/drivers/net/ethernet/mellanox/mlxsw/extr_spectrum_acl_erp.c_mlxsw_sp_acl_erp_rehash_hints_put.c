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
struct objagg_hints {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  objagg_hints_put (struct objagg_hints*) ; 

void mlxsw_sp_acl_erp_rehash_hints_put(void *hints_priv)
{
	struct objagg_hints *hints = hints_priv;

	objagg_hints_put(hints);
}