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
struct mdp5_kms {int dummy; } ;
struct mdp5_interface {int /*<<< orphan*/  type; } ;
struct mdp5_ctl {int /*<<< orphan*/  ctlm; } ;

/* Variables and functions */
 struct mdp5_kms* get_kms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdp5_cfg_intf_is_virtual (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_ctl_op (struct mdp5_ctl*,struct mdp5_pipeline*) ; 
 int /*<<< orphan*/  set_display_intf (struct mdp5_kms*,struct mdp5_interface*) ; 

int mdp5_ctl_set_pipeline(struct mdp5_ctl *ctl, struct mdp5_pipeline *pipeline)
{
	struct mdp5_kms *mdp5_kms = get_kms(ctl->ctlm);
	struct mdp5_interface *intf = pipeline->intf;

	/* Virtual interfaces need not set a display intf (e.g.: Writeback) */
	if (!mdp5_cfg_intf_is_virtual(intf->type))
		set_display_intf(mdp5_kms, intf);

	set_ctl_op(ctl, pipeline);

	return 0;
}