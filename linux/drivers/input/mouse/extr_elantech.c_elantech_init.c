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
struct psmouse {int dummy; } ;
struct elantech_device_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_MOUSE_ELAN_I2C_SMBUS ; 
 int /*<<< orphan*/  CONFIG_MOUSE_PS2_ELANTECH_SMBUS ; 
 int EINVAL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int PSMOUSE_ELANTECH ; 
 int PSMOUSE_ELANTECH_SMBUS ; 
 int elantech_query_info (struct psmouse*,struct elantech_device_info*) ; 
 int elantech_setup_ps2 (struct psmouse*,struct elantech_device_info*) ; 
 int elantech_setup_smbus (struct psmouse*,struct elantech_device_info*,int) ; 
 scalar_t__ elantech_use_host_notify (struct psmouse*,struct elantech_device_info*) ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_smbus_cleanup (struct psmouse*) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 

int elantech_init(struct psmouse *psmouse)
{
	struct elantech_device_info info;
	int error = -EINVAL;

	psmouse_reset(psmouse);

	error = elantech_query_info(psmouse, &info);
	if (error)
		goto init_fail;

#if defined(CONFIG_MOUSE_PS2_ELANTECH_SMBUS)

	if (elantech_use_host_notify(psmouse, &info)) {
		if (!IS_ENABLED(CONFIG_MOUSE_ELAN_I2C_SMBUS) ||
		    !IS_ENABLED(CONFIG_MOUSE_PS2_ELANTECH_SMBUS)) {
			psmouse_warn(psmouse,
				     "The touchpad can support a better bus than the too old PS/2 protocol. "
				     "Make sure MOUSE_PS2_ELANTECH_SMBUS and MOUSE_ELAN_I2C_SMBUS are enabled to get a better touchpad experience.\n");
		}
		error = elantech_setup_smbus(psmouse, &info, true);
		if (!error)
			return PSMOUSE_ELANTECH_SMBUS;
	}

#endif /* CONFIG_MOUSE_PS2_ELANTECH_SMBUS */

	error = elantech_setup_ps2(psmouse, &info);
	if (error < 0) {
		/*
		 * Not using any flavor of Elantech support, so clean up
		 * SMbus breadcrumbs, if any.
		 */
		psmouse_smbus_cleanup(psmouse);
		goto init_fail;
	}

	return PSMOUSE_ELANTECH;
 init_fail:
	psmouse_reset(psmouse);
	return error;
}