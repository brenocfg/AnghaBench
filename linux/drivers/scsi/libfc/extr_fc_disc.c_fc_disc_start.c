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
struct fc_disc {void (* disc_callback ) (struct fc_lport*,int) ;int /*<<< orphan*/  disc_mutex; } ;
struct fc_lport {struct fc_disc disc; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_disc_restart (struct fc_disc*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fc_disc_start(void (*disc_callback)(struct fc_lport *,
						enum fc_disc_event),
			  struct fc_lport *lport)
{
	struct fc_disc *disc = &lport->disc;

	/*
	 * At this point we may have a new disc job or an existing
	 * one. Either way, let's lock when we make changes to it
	 * and send the GPN_FT request.
	 */
	mutex_lock(&disc->disc_mutex);
	disc->disc_callback = disc_callback;
	fc_disc_restart(disc);
	mutex_unlock(&disc->disc_mutex);
}