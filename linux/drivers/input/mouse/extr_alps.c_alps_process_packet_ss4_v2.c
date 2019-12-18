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
struct psmouse {unsigned char* packet; struct input_dev* dev; struct alps_data* private; } ;
struct input_dev {int dummy; } ;
struct alps_fields {int fingers; int /*<<< orphan*/  pressure; int /*<<< orphan*/  middle; int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  ts_middle; int /*<<< orphan*/  ts_right; int /*<<< orphan*/  ts_left; scalar_t__ first_mp; scalar_t__ is_mp; } ;
struct alps_data {int multi_packet; unsigned char* multi_data; int flags; int /*<<< orphan*/  (* decode_fields ) (struct alps_fields*,unsigned char*,struct psmouse*) ;struct alps_fields f; struct input_dev* dev2; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS_PRESSURE ; 
 int ALPS_DUALPOINT ; 
 int /*<<< orphan*/  BTN_LEFT ; 
 int /*<<< orphan*/  BTN_MIDDLE ; 
 int /*<<< orphan*/  BTN_RIGHT ; 
 int /*<<< orphan*/  REL_X ; 
 int /*<<< orphan*/  REL_Y ; 
 scalar_t__ SS4_PACKET_ID_STICK ; 
 int /*<<< orphan*/  SS4_TS_X_V2 (unsigned char*) ; 
 int /*<<< orphan*/  SS4_TS_Y_V2 (unsigned char*) ; 
 int /*<<< orphan*/  SS4_TS_Z_V2 (unsigned char*) ; 
 scalar_t__ alps_get_pkt_id_ss4_v2 (unsigned char*) ; 
 int /*<<< orphan*/  alps_report_mt_data (struct psmouse*,int) ; 
 int /*<<< orphan*/  input_mt_report_finger_count (struct input_dev*,int) ; 
 int /*<<< orphan*/  input_report_abs (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_report_rel (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (struct alps_fields*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  psmouse_warn (struct psmouse*,char*) ; 
 int /*<<< orphan*/  stub1 (struct alps_fields*,unsigned char*,struct psmouse*) ; 
 int /*<<< orphan*/  stub2 (struct alps_fields*,unsigned char*,struct psmouse*) ; 

__attribute__((used)) static void alps_process_packet_ss4_v2(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;
	unsigned char *packet = psmouse->packet;
	struct input_dev *dev = psmouse->dev;
	struct input_dev *dev2 = priv->dev2;
	struct alps_fields *f = &priv->f;

	memset(f, 0, sizeof(struct alps_fields));
	priv->decode_fields(f, packet, psmouse);
	if (priv->multi_packet) {
		/*
		 * Sometimes the first packet will indicate a multi-packet
		 * sequence, but sometimes the next multi-packet would not
		 * come. Check for this, and when it happens process the
		 * position packet as usual.
		 */
		if (f->is_mp) {
			/* Now process the 1st packet */
			priv->decode_fields(f, priv->multi_data, psmouse);
		} else {
			priv->multi_packet = 0;
		}
	}

	/*
	 * "f.is_mp" would always be '0' after merging the 1st and 2nd packet.
	 * When it is set, it means 2nd packet comes without 1st packet come.
	 */
	if (f->is_mp)
		return;

	/* Save the first packet */
	if (!priv->multi_packet && f->first_mp) {
		priv->multi_packet = 1;
		memcpy(priv->multi_data, packet, sizeof(priv->multi_data));
		return;
	}

	priv->multi_packet = 0;

	/* Report trackstick */
	if (alps_get_pkt_id_ss4_v2(packet) == SS4_PACKET_ID_STICK) {
		if (!(priv->flags & ALPS_DUALPOINT)) {
			psmouse_warn(psmouse,
				     "Rejected trackstick packet from non DualPoint device");
			return;
		}

		input_report_rel(dev2, REL_X, SS4_TS_X_V2(packet));
		input_report_rel(dev2, REL_Y, SS4_TS_Y_V2(packet));
		input_report_abs(dev2, ABS_PRESSURE, SS4_TS_Z_V2(packet));

		input_report_key(dev2, BTN_LEFT, f->ts_left);
		input_report_key(dev2, BTN_RIGHT, f->ts_right);
		input_report_key(dev2, BTN_MIDDLE, f->ts_middle);

		input_sync(dev2);
		return;
	}

	/* Report touchpad */
	alps_report_mt_data(psmouse, (f->fingers <= 4) ? f->fingers : 4);

	input_mt_report_finger_count(dev, f->fingers);

	input_report_key(dev, BTN_LEFT, f->left);
	input_report_key(dev, BTN_RIGHT, f->right);
	input_report_key(dev, BTN_MIDDLE, f->middle);

	input_report_abs(dev, ABS_PRESSURE, f->pressure);
	input_sync(dev);
}