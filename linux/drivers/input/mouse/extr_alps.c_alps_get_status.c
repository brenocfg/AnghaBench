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
 int /*<<< orphan*/  PSMOUSE_CMD_DISABLE ; 
 scalar_t__ alps_rpt_cmd (struct psmouse*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int alps_get_status(struct psmouse *psmouse, char *param)
{
	/* Get status: 0xF5 0xF5 0xF5 0xE9 */
	if (alps_rpt_cmd(psmouse, 0, PSMOUSE_CMD_DISABLE, param))
		return -1;

	return 0;
}