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
struct TYPE_6__ {TYPE_2__* serio; } ;
struct psmouse {int pktsize; struct fsp_data* private; TYPE_3__ ps2dev; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  reconnect; int /*<<< orphan*/  disconnect; int /*<<< orphan*/  protocol_handler; } ;
struct fsp_data {int ver; int rev; } ;
struct TYPE_4__ {int /*<<< orphan*/  kobj; } ;
struct TYPE_5__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int FSP_VER_STL3888_C0 ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int fsp_activate_protocol (struct psmouse*) ; 
 int /*<<< orphan*/  fsp_attribute_group ; 
 int /*<<< orphan*/  fsp_disconnect ; 
 int /*<<< orphan*/  fsp_drv_ver ; 
 scalar_t__ fsp_get_revision (struct psmouse*,int*) ; 
 int /*<<< orphan*/  fsp_get_sn (struct psmouse*,int*) ; 
 scalar_t__ fsp_get_version (struct psmouse*,int*) ; 
 int /*<<< orphan*/  fsp_process_byte ; 
 int /*<<< orphan*/  fsp_reconnect ; 
 int /*<<< orphan*/  fsp_reset ; 
 int fsp_set_input_params (struct psmouse*) ; 
 int /*<<< orphan*/  kfree (struct fsp_data*) ; 
 struct fsp_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*,int) ; 
 int /*<<< orphan*/  psmouse_info (struct psmouse*,char*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int fsp_init(struct psmouse *psmouse)
{
	struct fsp_data *priv;
	int ver, rev, sn = 0;
	int error;

	if (fsp_get_version(psmouse, &ver) ||
	    fsp_get_revision(psmouse, &rev)) {
		return -ENODEV;
	}
	if (ver >= FSP_VER_STL3888_C0) {
		/* firmware information is only available since C0 */
		fsp_get_sn(psmouse, &sn);
	}

	psmouse_info(psmouse,
		     "Finger Sensing Pad, hw: %d.%d.%d, sn: %x, sw: %s\n",
		     ver >> 4, ver & 0x0F, rev, sn, fsp_drv_ver);

	psmouse->private = priv = kzalloc(sizeof(struct fsp_data), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->ver = ver;
	priv->rev = rev;

	psmouse->protocol_handler = fsp_process_byte;
	psmouse->disconnect = fsp_disconnect;
	psmouse->reconnect = fsp_reconnect;
	psmouse->cleanup = fsp_reset;
	psmouse->pktsize = 4;

	error = fsp_activate_protocol(psmouse);
	if (error)
		goto err_out;

	/* Set up various supported input event bits */
	error = fsp_set_input_params(psmouse);
	if (error)
		goto err_out;

	error = sysfs_create_group(&psmouse->ps2dev.serio->dev.kobj,
				   &fsp_attribute_group);
	if (error) {
		psmouse_err(psmouse,
			    "Failed to create sysfs attributes (%d)", error);
		goto err_out;
	}

	return 0;

 err_out:
	kfree(psmouse->private);
	psmouse->private = NULL;
	return error;
}