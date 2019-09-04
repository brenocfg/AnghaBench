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
struct psmouse {struct input_dev* dev; struct hgpk_data* private; } ;
struct input_dev {int dummy; } ;
struct hgpk_data {int mode; } ;
typedef  size_t ssize_t ;
typedef  enum hgpk_mode { ____Placeholder_hgpk_mode } hgpk_mode ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENOMEM ; 
 int HGPK_MODE_INVALID ; 
 int /*<<< orphan*/  PSMOUSE_CMD_MODE ; 
 int /*<<< orphan*/  PSMOUSE_INITIALIZING ; 
 int hgpk_mode_from_name (char const*,size_t) ; 
 int hgpk_reset_device (struct psmouse*,int) ; 
 int /*<<< orphan*/  hgpk_setup_input_device (struct input_dev*,struct input_dev*,int) ; 
 struct input_dev* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (struct input_dev*) ; 
 int input_register_device (struct input_dev*) ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_set_state (struct psmouse*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t attr_set_mode(struct psmouse *psmouse, void *data,
			     const char *buf, size_t len)
{
	struct hgpk_data *priv = psmouse->private;
	enum hgpk_mode old_mode = priv->mode;
	enum hgpk_mode new_mode = hgpk_mode_from_name(buf, len);
	struct input_dev *old_dev = psmouse->dev;
	struct input_dev *new_dev;
	int err;

	if (new_mode == HGPK_MODE_INVALID)
		return -EINVAL;

	if (old_mode == new_mode)
		return len;

	new_dev = input_allocate_device();
	if (!new_dev)
		return -ENOMEM;

	psmouse_set_state(psmouse, PSMOUSE_INITIALIZING);

	/* Switch device into the new mode */
	priv->mode = new_mode;
	err = hgpk_reset_device(psmouse, false);
	if (err)
		goto err_try_restore;

	hgpk_setup_input_device(new_dev, old_dev, new_mode);

	psmouse_set_state(psmouse, PSMOUSE_CMD_MODE);

	err = input_register_device(new_dev);
	if (err)
		goto err_try_restore;

	psmouse->dev = new_dev;
	input_unregister_device(old_dev);

	return len;

err_try_restore:
	input_free_device(new_dev);
	priv->mode = old_mode;
	hgpk_reset_device(psmouse, false);

	return err;
}