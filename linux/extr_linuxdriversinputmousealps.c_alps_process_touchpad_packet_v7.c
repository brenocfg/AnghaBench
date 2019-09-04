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
struct psmouse {int /*<<< orphan*/  packet; struct input_dev* dev; struct alps_data* private; } ;
struct input_dev {int dummy; } ;
struct alps_fields {int /*<<< orphan*/  middle; int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  fingers; int /*<<< orphan*/  mt; } ;
struct alps_data {scalar_t__ (* decode_fields ) (struct alps_fields*,int /*<<< orphan*/ ,struct psmouse*) ;struct alps_fields f; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  alps_get_mt_count (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alps_report_mt_data (struct psmouse*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_mt_report_finger_count (struct input_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  memset (struct alps_fields*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub1 (struct alps_fields*,int /*<<< orphan*/ ,struct psmouse*) ; 

__attribute__((used)) static void alps_process_touchpad_packet_v7(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;
	struct input_dev *dev = psmouse->dev;
	struct alps_fields *f = &priv->f;

	memset(f, 0, sizeof(*f));

	if (priv->decode_fields(f, psmouse->packet, psmouse))
		return;

	alps_report_mt_data(psmouse, alps_get_mt_count(f->mt));

	input_mt_report_finger_count(dev, f->fingers);

	input_report_key(dev, BTN_LEFT, f->left);
	input_report_key(dev, BTN_RIGHT, f->right);
	input_report_key(dev, BTN_MIDDLE, f->middle);

	input_sync(dev);
}