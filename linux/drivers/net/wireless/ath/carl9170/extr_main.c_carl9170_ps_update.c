#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int state; void* last_action; void* last_slept; int /*<<< orphan*/  sleep_ms; int /*<<< orphan*/  off_override; } ;
struct ar9170 {TYPE_3__ ps; TYPE_2__* hw; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ conf; } ;

/* Variables and functions */
 int IEEE80211_CONF_PS ; 
 int carl9170_powersave (struct ar9170*,int) ; 
 void* jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (void*) ; 

__attribute__((used)) static int carl9170_ps_update(struct ar9170 *ar)
{
	bool ps = false;
	int err = 0;

	if (!ar->ps.off_override)
		ps = (ar->hw->conf.flags & IEEE80211_CONF_PS);

	if (ps != ar->ps.state) {
		err = carl9170_powersave(ar, ps);
		if (err)
			return err;

		if (ar->ps.state && !ps) {
			ar->ps.sleep_ms = jiffies_to_msecs(jiffies -
				ar->ps.last_action);
		}

		if (ps)
			ar->ps.last_slept = jiffies;

		ar->ps.last_action = jiffies;
		ar->ps.state = ps;
	}

	return 0;
}