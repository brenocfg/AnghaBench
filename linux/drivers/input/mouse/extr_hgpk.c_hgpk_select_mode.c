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
struct ps2dev {int dummy; } ;
struct psmouse {int pktsize; struct hgpk_data* private; struct ps2dev ps2dev; } ;
struct hgpk_data {int mode; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 
 int EINVAL ; 
 int EIO ; 
#define  HGPK_MODE_GLIDESENSOR 130 
#define  HGPK_MODE_MOUSE 129 
#define  HGPK_MODE_PENTABLET 128 
 int PSMOUSE_CMD_DISABLE ; 
 int PSMOUSE_CMD_SETSCALE11 ; 
 int PSMOUSE_CMD_SETSCALE21 ; 
 int /*<<< orphan*/  ps2_command (struct ps2dev*,int /*<<< orphan*/ *,int const) ; 

__attribute__((used)) static int hgpk_select_mode(struct psmouse *psmouse)
{
	struct ps2dev *ps2dev = &psmouse->ps2dev;
	struct hgpk_data *priv = psmouse->private;
	int i;
	int cmd;

	/*
	 * 4 disables to enable advanced mode
	 * then 3 0xf2 bytes as the preamble for GS/PT selection
	 */
	const int advanced_init[] = {
		PSMOUSE_CMD_DISABLE, PSMOUSE_CMD_DISABLE,
		PSMOUSE_CMD_DISABLE, PSMOUSE_CMD_DISABLE,
		0xf2, 0xf2, 0xf2,
	};

	switch (priv->mode) {
	case HGPK_MODE_MOUSE:
		psmouse->pktsize = 3;
		break;

	case HGPK_MODE_GLIDESENSOR:
	case HGPK_MODE_PENTABLET:
		psmouse->pktsize = 6;

		/* Switch to 'Advanced mode.', four disables in a row. */
		for (i = 0; i < ARRAY_SIZE(advanced_init); i++)
			if (ps2_command(ps2dev, NULL, advanced_init[i]))
				return -EIO;

		/* select between GlideSensor (mouse) or PenTablet */
		cmd = priv->mode == HGPK_MODE_GLIDESENSOR ?
			PSMOUSE_CMD_SETSCALE11 : PSMOUSE_CMD_SETSCALE21;

		if (ps2_command(ps2dev, NULL, cmd))
			return -EIO;
		break;

	default:
		return -EINVAL;
	}

	return 0;
}