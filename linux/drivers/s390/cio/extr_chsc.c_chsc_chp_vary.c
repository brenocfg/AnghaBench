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
struct chp_id {int dummy; } ;
struct channel_path {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  chp_update_desc (struct channel_path*) ; 
 struct channel_path* chpid_to_chp (struct chp_id) ; 
 int /*<<< orphan*/  css_schedule_reprobe () ; 
 int /*<<< orphan*/  css_wait_for_slow_path () ; 
 int /*<<< orphan*/  for_each_subchannel_staged (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct chp_id*) ; 
 int /*<<< orphan*/  s390_subchannel_vary_chpid_off ; 
 int /*<<< orphan*/  s390_subchannel_vary_chpid_on ; 

int chsc_chp_vary(struct chp_id chpid, int on)
{
	struct channel_path *chp = chpid_to_chp(chpid);

	/* Wait until previous actions have settled. */
	css_wait_for_slow_path();
	/*
	 * Redo PathVerification on the devices the chpid connects to
	 */
	if (on) {
		/* Try to update the channel path description. */
		chp_update_desc(chp);
		for_each_subchannel_staged(s390_subchannel_vary_chpid_on,
					   NULL, &chpid);
		css_schedule_reprobe();
	} else
		for_each_subchannel_staged(s390_subchannel_vary_chpid_off,
					   NULL, &chpid);

	return 0;
}