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
struct sfp {unsigned int state; int /*<<< orphan*/  st_mutex; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned int BIT (unsigned int) ; 
 unsigned int GPIO_MAX ; 
 int /*<<< orphan*/  SFP_E_INSERT ; 
 int /*<<< orphan*/  SFP_E_LOS_HIGH ; 
 int /*<<< orphan*/  SFP_E_LOS_LOW ; 
 int /*<<< orphan*/  SFP_E_REMOVE ; 
 int /*<<< orphan*/  SFP_E_TX_CLEAR ; 
 int /*<<< orphan*/  SFP_E_TX_FAULT ; 
 unsigned int SFP_F_LOS ; 
 unsigned int SFP_F_PRESENT ; 
 unsigned int SFP_F_RATE_SELECT ; 
 unsigned int SFP_F_TX_DISABLE ; 
 unsigned int SFP_F_TX_FAULT ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * gpio_of_names ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 unsigned int sfp_get_state (struct sfp*) ; 
 int /*<<< orphan*/  sfp_sm_event (struct sfp*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sfp_check_state(struct sfp *sfp)
{
	unsigned int state, i, changed;

	mutex_lock(&sfp->st_mutex);
	state = sfp_get_state(sfp);
	changed = state ^ sfp->state;
	changed &= SFP_F_PRESENT | SFP_F_LOS | SFP_F_TX_FAULT;

	for (i = 0; i < GPIO_MAX; i++)
		if (changed & BIT(i))
			dev_dbg(sfp->dev, "%s %u -> %u\n", gpio_of_names[i],
				!!(sfp->state & BIT(i)), !!(state & BIT(i)));

	state |= sfp->state & (SFP_F_TX_DISABLE | SFP_F_RATE_SELECT);
	sfp->state = state;

	rtnl_lock();
	if (changed & SFP_F_PRESENT)
		sfp_sm_event(sfp, state & SFP_F_PRESENT ?
				SFP_E_INSERT : SFP_E_REMOVE);

	if (changed & SFP_F_TX_FAULT)
		sfp_sm_event(sfp, state & SFP_F_TX_FAULT ?
				SFP_E_TX_FAULT : SFP_E_TX_CLEAR);

	if (changed & SFP_F_LOS)
		sfp_sm_event(sfp, state & SFP_F_LOS ?
				SFP_E_LOS_HIGH : SFP_E_LOS_LOW);
	rtnl_unlock();
	mutex_unlock(&sfp->st_mutex);
}