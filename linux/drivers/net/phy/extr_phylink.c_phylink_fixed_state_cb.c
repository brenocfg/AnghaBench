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
struct phylink {scalar_t__ link_an_mode; void (* get_fixed_state ) (struct net_device*,struct phylink_link_state*) ;int /*<<< orphan*/  state_mutex; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MLO_AN_FIXED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int phylink_fixed_state_cb(struct phylink *pl,
			   void (*cb)(struct net_device *dev,
				      struct phylink_link_state *state))
{
	/* It does not make sense to let the link be overriden unless we use
	 * MLO_AN_FIXED
	 */
	if (pl->link_an_mode != MLO_AN_FIXED)
		return -EINVAL;

	mutex_lock(&pl->state_mutex);
	pl->get_fixed_state = cb;
	mutex_unlock(&pl->state_mutex);

	return 0;
}