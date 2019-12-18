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
struct hfi1_pportdata {int /*<<< orphan*/  cc_state_lock; int /*<<< orphan*/  cc_state; } ;
struct cc_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 struct cc_state* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
struct cc_state *get_cc_state_protected(struct hfi1_pportdata *ppd)
{
	return rcu_dereference_protected(ppd->cc_state,
					 lockdep_is_held(&ppd->cc_state_lock));
}