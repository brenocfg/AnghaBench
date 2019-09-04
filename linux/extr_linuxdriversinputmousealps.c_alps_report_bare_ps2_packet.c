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
struct psmouse {struct input_dev* dev; struct alps_data* private; } ;
struct input_dev {int dummy; } ;
struct alps_data {scalar_t__ proto_version; int flags; struct input_dev* dev3; int /*<<< orphan*/  dev3_register_work; struct input_dev* dev2; } ;

/* Variables and functions */
 int ALPS_DUALPOINT ; 
 scalar_t__ ALPS_PROTO_V2 ; 
 int /*<<< orphan*/  IS_ERR (struct input_dev*) ; 
 int /*<<< orphan*/  IS_ERR_OR_NULL (struct input_dev*) ; 
 int /*<<< orphan*/  alps_report_buttons (struct input_dev*,struct input_dev*,unsigned char,unsigned char,unsigned char) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  psmouse_queue_work (struct psmouse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psmouse_report_standard_motion (struct input_dev*,unsigned char*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void alps_report_bare_ps2_packet(struct psmouse *psmouse,
					unsigned char packet[],
					bool report_buttons)
{
	struct alps_data *priv = psmouse->private;
	struct input_dev *dev, *dev2 = NULL;

	/* Figure out which device to use to report the bare packet */
	if (priv->proto_version == ALPS_PROTO_V2 &&
	    (priv->flags & ALPS_DUALPOINT)) {
		/* On V2 devices the DualPoint Stick reports bare packets */
		dev = priv->dev2;
		dev2 = psmouse->dev;
	} else if (unlikely(IS_ERR_OR_NULL(priv->dev3))) {
		/* Register dev3 mouse if we received PS/2 packet first time */
		if (!IS_ERR(priv->dev3))
			psmouse_queue_work(psmouse, &priv->dev3_register_work,
					   0);
		return;
	} else {
		dev = priv->dev3;
	}

	if (report_buttons)
		alps_report_buttons(dev, dev2,
				packet[0] & 1, packet[0] & 2, packet[0] & 4);

	psmouse_report_standard_motion(dev, packet);

	input_sync(dev);
}