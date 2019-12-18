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
struct fc_lport {int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  retry_work; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_TYPE_CT ; 
 int /*<<< orphan*/  FC_TYPE_FCP ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LPORT_ST_DISABLED ; 
 int /*<<< orphan*/  fc_fc4_conf_lport_params (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_lport_add_fc4_type (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_lport_state_enter (struct fc_lport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fc_lport_timeout ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

int fc_lport_config(struct fc_lport *lport)
{
	INIT_DELAYED_WORK(&lport->retry_work, fc_lport_timeout);
	mutex_init(&lport->lp_mutex);

	fc_lport_state_enter(lport, LPORT_ST_DISABLED);

	fc_lport_add_fc4_type(lport, FC_TYPE_FCP);
	fc_lport_add_fc4_type(lport, FC_TYPE_CT);
	fc_fc4_conf_lport_params(lport, FC_TYPE_FCP);

	return 0;
}