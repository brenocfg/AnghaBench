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
struct psmouse {struct hgpk_data* private; } ;
struct hgpk_data {int powered; int /*<<< orphan*/  recalib_wq; int /*<<< orphan*/  mode; struct psmouse* psmouse; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hgpk_default_mode ; 
 int /*<<< orphan*/  hgpk_recalib_work ; 
 int hgpk_register (struct psmouse*) ; 
 int hgpk_reset_device (struct psmouse*,int) ; 
 int /*<<< orphan*/  kfree (struct hgpk_data*) ; 
 struct hgpk_data* kzalloc (int,int /*<<< orphan*/ ) ; 

int hgpk_init(struct psmouse *psmouse)
{
	struct hgpk_data *priv;
	int err;

	priv = kzalloc(sizeof(struct hgpk_data), GFP_KERNEL);
	if (!priv) {
		err = -ENOMEM;
		goto alloc_fail;
	}

	psmouse->private = priv;

	priv->psmouse = psmouse;
	priv->powered = true;
	priv->mode = hgpk_default_mode;
	INIT_DELAYED_WORK(&priv->recalib_wq, hgpk_recalib_work);

	err = hgpk_reset_device(psmouse, false);
	if (err)
		goto init_fail;

	err = hgpk_register(psmouse);
	if (err)
		goto init_fail;

	return 0;

init_fail:
	kfree(priv);
alloc_fail:
	return err;
}