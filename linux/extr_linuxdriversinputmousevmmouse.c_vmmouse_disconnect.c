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
struct vmmouse_data {int /*<<< orphan*/  abs_dev; } ;
struct psmouse {struct vmmouse_data* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct vmmouse_data*) ; 
 int /*<<< orphan*/  psmouse_reset (struct psmouse*) ; 
 int /*<<< orphan*/  vmmouse_disable (struct psmouse*) ; 

__attribute__((used)) static void vmmouse_disconnect(struct psmouse *psmouse)
{
	struct vmmouse_data *priv = psmouse->private;

	vmmouse_disable(psmouse);
	psmouse_reset(psmouse);
	input_unregister_device(priv->abs_dev);
	kfree(priv);
}