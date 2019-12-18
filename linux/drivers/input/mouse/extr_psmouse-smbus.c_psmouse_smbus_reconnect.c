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
struct psmouse_smbus_dev {scalar_t__ need_deactivate; } ;
struct psmouse {struct psmouse_smbus_dev* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  psmouse_deactivate (struct psmouse*) ; 

__attribute__((used)) static int psmouse_smbus_reconnect(struct psmouse *psmouse)
{
	struct psmouse_smbus_dev *smbdev = psmouse->private;

	if (smbdev->need_deactivate)
		psmouse_deactivate(psmouse);

	return 0;
}