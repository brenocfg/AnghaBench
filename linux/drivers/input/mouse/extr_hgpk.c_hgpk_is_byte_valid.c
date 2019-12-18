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
struct psmouse {int pktcnt; int /*<<< orphan*/  packet; struct hgpk_data* private; } ;
struct hgpk_data {int mode; } ;

/* Variables and functions */
 unsigned char HGPK_GS ; 
#define  HGPK_MODE_GLIDESENSOR 130 
#define  HGPK_MODE_MOUSE 129 
#define  HGPK_MODE_PENTABLET 128 
 unsigned char HGPK_PT ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool hgpk_is_byte_valid(struct psmouse *psmouse, unsigned char *packet)
{
	struct hgpk_data *priv = psmouse->private;
	int pktcnt = psmouse->pktcnt;
	bool valid;

	switch (priv->mode) {
	case HGPK_MODE_MOUSE:
		valid = (packet[0] & 0x0C) == 0x08;
		break;

	case HGPK_MODE_GLIDESENSOR:
		valid = pktcnt == 1 ?
			packet[0] == HGPK_GS : !(packet[pktcnt - 1] & 0x80);
		break;

	case HGPK_MODE_PENTABLET:
		valid = pktcnt == 1 ?
			packet[0] == HGPK_PT : !(packet[pktcnt - 1] & 0x80);
		break;

	default:
		valid = false;
		break;
	}

	if (!valid)
		psmouse_dbg(psmouse,
			    "bad data, mode %d (%d) %*ph\n",
			    priv->mode, pktcnt, 6, psmouse->packet);

	return valid;
}