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
struct TYPE_5__ {TYPE_1__* serio; } ;
struct psmouse {int pktsize; TYPE_2__ ps2dev; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  set_resolution; int /*<<< orphan*/  protocol_handler; } ;
struct ps2pp_info {scalar_t__ kind; } ;
struct TYPE_6__ {int /*<<< orphan*/  dattr; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ PS2PP_KIND_TP3 ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ps2pp_disconnect ; 
 int /*<<< orphan*/  ps2pp_process_byte ; 
 int /*<<< orphan*/  ps2pp_set_resolution ; 
 TYPE_3__ psmouse_attr_smartscroll ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*,int) ; 

__attribute__((used)) static int ps2pp_setup_protocol(struct psmouse *psmouse,
				const struct ps2pp_info *model_info)
{
	int error;

	psmouse->protocol_handler = ps2pp_process_byte;
	psmouse->pktsize = 3;

	if (model_info->kind != PS2PP_KIND_TP3) {
		psmouse->set_resolution = ps2pp_set_resolution;
		psmouse->disconnect = ps2pp_disconnect;

		error = device_create_file(&psmouse->ps2dev.serio->dev,
					   &psmouse_attr_smartscroll.dattr);
		if (error) {
			psmouse_err(psmouse,
				    "failed to create smartscroll sysfs attribute, error: %d\n",
				    error);
			return error;
		}
	}

	return 0;
}