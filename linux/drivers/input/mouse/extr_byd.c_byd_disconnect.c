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
struct psmouse {struct byd_data* private; } ;
struct byd_data {int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct byd_data*) ; 

__attribute__((used)) static void byd_disconnect(struct psmouse *psmouse)
{
	struct byd_data *priv = psmouse->private;

	if (priv) {
		del_timer(&priv->timer);
		kfree(psmouse->private);
		psmouse->private = NULL;
	}
}