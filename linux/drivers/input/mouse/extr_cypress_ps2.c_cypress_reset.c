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
struct psmouse {struct cytp_data* private; } ;
struct cytp_data {scalar_t__ mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 

__attribute__((used)) static void cypress_reset(struct psmouse *psmouse)
{
	struct cytp_data *cytp = psmouse->private;

	cytp->mode = 0;

	psmouse_reset(psmouse);
}