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
struct psmouse {struct alps_data* private; } ;
struct alps_data {int (* hw_init ) (struct psmouse*) ;} ;

/* Variables and functions */
 scalar_t__ alps_identify (struct psmouse*,struct alps_data*) ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 
 int stub1 (struct psmouse*) ; 

__attribute__((used)) static int alps_reconnect(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;

	psmouse_reset(psmouse);

	if (alps_identify(psmouse, priv) < 0)
		return -1;

	return priv->hw_init(psmouse);
}