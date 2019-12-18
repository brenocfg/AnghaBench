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
struct psmouse {int* packet; int pktcnt; int pktsize; int /*<<< orphan*/  out_of_sync_cnt; struct alps_data* private; } ;
struct alps_data {scalar_t__ proto_version; int flags; int /*<<< orphan*/  (* process_packet ) (struct psmouse*) ;int /*<<< orphan*/  byte0; int /*<<< orphan*/  mask0; } ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
 scalar_t__ ALPS_PROTO_V3_RUSHMORE ; 
 scalar_t__ ALPS_PROTO_V5 ; 
 scalar_t__ ALPS_PROTO_V7 ; 
 scalar_t__ ALPS_PROTO_V8 ; 
 int ALPS_PS2_INTERLEAVED ; 
 int /*<<< orphan*/  PSMOUSE_BAD_DATA ; 
 int /*<<< orphan*/  PSMOUSE_FULL_PACKET ; 
 int /*<<< orphan*/  PSMOUSE_GOOD_DATA ; 
 int /*<<< orphan*/  alps_handle_interleaved_ps2 (struct psmouse*) ; 
 int /*<<< orphan*/  alps_is_valid_first_byte (struct alps_data*,int) ; 
 int /*<<< orphan*/  alps_is_valid_package_ss4_v2 (struct psmouse*) ; 
 int /*<<< orphan*/  alps_is_valid_package_v7 (struct psmouse*) ; 
 int /*<<< orphan*/  alps_report_bare_ps2_packet (struct psmouse*,int*,int) ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*,int,int,...) ; 
 int /*<<< orphan*/  stub1 (struct psmouse*) ; 

__attribute__((used)) static psmouse_ret_t alps_process_byte(struct psmouse *psmouse)
{
	struct alps_data *priv = psmouse->private;

	/*
	 * Check if we are dealing with a bare PS/2 packet, presumably from
	 * a device connected to the external PS/2 port. Because bare PS/2
	 * protocol does not have enough constant bits to self-synchronize
	 * properly we only do this if the device is fully synchronized.
	 * Can not distinguish V8's first byte from PS/2 packet's
	 */
	if (priv->proto_version != ALPS_PROTO_V8 &&
	    !psmouse->out_of_sync_cnt &&
	    (psmouse->packet[0] & 0xc8) == 0x08) {

		if (psmouse->pktcnt == 3) {
			alps_report_bare_ps2_packet(psmouse, psmouse->packet,
						    true);
			return PSMOUSE_FULL_PACKET;
		}
		return PSMOUSE_GOOD_DATA;
	}

	/* Check for PS/2 packet stuffed in the middle of ALPS packet. */

	if ((priv->flags & ALPS_PS2_INTERLEAVED) &&
	    psmouse->pktcnt >= 4 && (psmouse->packet[3] & 0x0f) == 0x0f) {
		return alps_handle_interleaved_ps2(psmouse);
	}

	if (!alps_is_valid_first_byte(priv, psmouse->packet[0])) {
		psmouse_dbg(psmouse,
			    "refusing packet[0] = %x (mask0 = %x, byte0 = %x)\n",
			    psmouse->packet[0], priv->mask0, priv->byte0);
		return PSMOUSE_BAD_DATA;
	}

	/* Bytes 2 - pktsize should have 0 in the highest bit */
	if (priv->proto_version < ALPS_PROTO_V5 &&
	    psmouse->pktcnt >= 2 && psmouse->pktcnt <= psmouse->pktsize &&
	    (psmouse->packet[psmouse->pktcnt - 1] & 0x80)) {
		psmouse_dbg(psmouse, "refusing packet[%i] = %x\n",
			    psmouse->pktcnt - 1,
			    psmouse->packet[psmouse->pktcnt - 1]);

		if (priv->proto_version == ALPS_PROTO_V3_RUSHMORE &&
		    psmouse->pktcnt == psmouse->pktsize) {
			/*
			 * Some Dell boxes, such as Latitude E6440 or E7440
			 * with closed lid, quite often smash last byte of
			 * otherwise valid packet with 0xff. Given that the
			 * next packet is very likely to be valid let's
			 * report PSMOUSE_FULL_PACKET but not process data,
			 * rather than reporting PSMOUSE_BAD_DATA and
			 * filling the logs.
			 */
			return PSMOUSE_FULL_PACKET;
		}

		return PSMOUSE_BAD_DATA;
	}

	if ((priv->proto_version == ALPS_PROTO_V7 &&
			!alps_is_valid_package_v7(psmouse)) ||
	    (priv->proto_version == ALPS_PROTO_V8 &&
			!alps_is_valid_package_ss4_v2(psmouse))) {
		psmouse_dbg(psmouse, "refusing packet[%i] = %x\n",
			    psmouse->pktcnt - 1,
			    psmouse->packet[psmouse->pktcnt - 1]);
		return PSMOUSE_BAD_DATA;
	}

	if (psmouse->pktcnt == psmouse->pktsize) {
		priv->process_packet(psmouse);
		return PSMOUSE_FULL_PACKET;
	}

	return PSMOUSE_GOOD_DATA;
}