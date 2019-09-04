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
struct alps_data {scalar_t__ dev3; scalar_t__ dev2; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR_OR_NULL (scalar_t__) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  input_unregister_device (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct alps_data*) ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 

__attribute__((used)) static void alps_disconnect(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;

	psmouse_reset(psmouse);
	del_timer_sync(&priv->timer);
	if (priv->dev2)
		input_unregister_device(priv->dev2);
	if (!IS_ERR_OR_NULL(priv->dev3))
		input_unregister_device(priv->dev3);
	kfree(priv);
}