#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* serio; } ;
struct psmouse {int resetafter; scalar_t__ model; TYPE_2__ ps2dev; int /*<<< orphan*/  dev; scalar_t__ resync_time; int /*<<< orphan*/  reconnect; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  poll; int /*<<< orphan*/  protocol_handler; struct hgpk_data* private; } ;
struct hgpk_data {int /*<<< orphan*/  mode; } ;
struct TYPE_10__ {int /*<<< orphan*/  dattr; } ;
struct TYPE_9__ {int /*<<< orphan*/  dattr; } ;
struct TYPE_8__ {int /*<<< orphan*/  dattr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ HGPK_MODEL_C ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hgpk_disconnect ; 
 int /*<<< orphan*/  hgpk_poll ; 
 int /*<<< orphan*/  hgpk_process_byte ; 
 int /*<<< orphan*/  hgpk_reconnect ; 
 int /*<<< orphan*/  hgpk_setup_input_device (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__ psmouse_attr_hgpk_mode ; 
 TYPE_4__ psmouse_attr_powered ; 
 TYPE_3__ psmouse_attr_recalibrate ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*) ; 

__attribute__((used)) static int hgpk_register(struct psmouse *psmouse)
{
	struct hgpk_data *priv = psmouse->private;
	int err;

	/* register handlers */
	psmouse->protocol_handler = hgpk_process_byte;
	psmouse->poll = hgpk_poll;
	psmouse->disconnect = hgpk_disconnect;
	psmouse->reconnect = hgpk_reconnect;

	/* Disable the idle resync. */
	psmouse->resync_time = 0;
	/* Reset after a lot of bad bytes. */
	psmouse->resetafter = 1024;

	hgpk_setup_input_device(psmouse->dev, NULL, priv->mode);

	err = device_create_file(&psmouse->ps2dev.serio->dev,
				 &psmouse_attr_powered.dattr);
	if (err) {
		psmouse_err(psmouse, "Failed creating 'powered' sysfs node\n");
		return err;
	}

	err = device_create_file(&psmouse->ps2dev.serio->dev,
				 &psmouse_attr_hgpk_mode.dattr);
	if (err) {
		psmouse_err(psmouse,
			    "Failed creating 'hgpk_mode' sysfs node\n");
		goto err_remove_powered;
	}

	/* C-series touchpads added the recalibrate command */
	if (psmouse->model >= HGPK_MODEL_C) {
		err = device_create_file(&psmouse->ps2dev.serio->dev,
					 &psmouse_attr_recalibrate.dattr);
		if (err) {
			psmouse_err(psmouse,
				    "Failed creating 'recalibrate' sysfs node\n");
			goto err_remove_mode;
		}
	}

	return 0;

err_remove_mode:
	device_remove_file(&psmouse->ps2dev.serio->dev,
			   &psmouse_attr_hgpk_mode.dattr);
err_remove_powered:
	device_remove_file(&psmouse->ps2dev.serio->dev,
			   &psmouse_attr_powered.dattr);
	return err;
}