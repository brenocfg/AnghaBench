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

/* Variables and functions */
 int /*<<< orphan*/  psmouse_err (struct psmouse*,char*,int) ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 
 int /*<<< orphan*/  vmmouse_disable (struct psmouse*) ; 
 int vmmouse_enable (struct psmouse*) ; 

__attribute__((used)) static int vmmouse_reconnect(struct psmouse *psmouse)
{
	int error;

	psmouse_reset(psmouse);
	vmmouse_disable(psmouse);
	error = vmmouse_enable(psmouse);
	if (error) {
		psmouse_err(psmouse,
			    "Unable to re-enable mouse when reconnecting, err: %d\n",
			    error);
		return error;
	}

	return 0;
}