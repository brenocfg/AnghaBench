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
typedef  int /*<<< orphan*/  u32 ;
struct fc_lport {int state; int /*<<< orphan*/  lp_mutex; } ;

/* Variables and functions */
#define  LPORT_ST_FLOGI 129 
#define  LPORT_ST_RESET 128 
 int /*<<< orphan*/  fc_lport_enter_ready (struct fc_lport*) ; 
 int /*<<< orphan*/  fc_lport_set_port_id (struct fc_lport*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void fc_lport_set_local_id(struct fc_lport *lport, u32 port_id)
{
	mutex_lock(&lport->lp_mutex);

	fc_lport_set_port_id(lport, port_id, NULL);

	switch (lport->state) {
	case LPORT_ST_RESET:
	case LPORT_ST_FLOGI:
		if (port_id)
			fc_lport_enter_ready(lport);
		break;
	default:
		break;
	}
	mutex_unlock(&lport->lp_mutex);
}