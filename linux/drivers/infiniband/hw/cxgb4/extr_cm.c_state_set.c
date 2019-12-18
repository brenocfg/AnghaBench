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
struct c4iw_ep_common {size_t state; int /*<<< orphan*/  mutex; } ;
typedef  enum c4iw_ep_state { ____Placeholder_c4iw_ep_state } c4iw_ep_state ;

/* Variables and functions */
 int /*<<< orphan*/  __state_set (struct c4iw_ep_common*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * states ; 

__attribute__((used)) static void state_set(struct c4iw_ep_common *epc, enum c4iw_ep_state new)
{
	mutex_lock(&epc->mutex);
	pr_debug("%s -> %s\n", states[epc->state], states[new]);
	__state_set(epc, new);
	mutex_unlock(&epc->mutex);
	return;
}