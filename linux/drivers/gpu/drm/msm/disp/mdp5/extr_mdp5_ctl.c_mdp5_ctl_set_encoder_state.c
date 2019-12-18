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
struct mdp5_pipeline {struct mdp5_interface* intf; } ;
struct mdp5_interface {int /*<<< orphan*/  num; } ;
struct mdp5_ctl {int encoder_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  send_start_signal (struct mdp5_ctl*) ; 
 scalar_t__ start_signal_needed (struct mdp5_ctl*,struct mdp5_pipeline*) ; 

int mdp5_ctl_set_encoder_state(struct mdp5_ctl *ctl,
			       struct mdp5_pipeline *pipeline,
			       bool enabled)
{
	struct mdp5_interface *intf = pipeline->intf;

	if (WARN_ON(!ctl))
		return -EINVAL;

	ctl->encoder_enabled = enabled;
	DBG("intf_%d: %s", intf->num, enabled ? "on" : "off");

	if (start_signal_needed(ctl, pipeline)) {
		send_start_signal(ctl);
	}

	return 0;
}