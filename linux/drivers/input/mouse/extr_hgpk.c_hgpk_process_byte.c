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
struct psmouse {scalar_t__ pktcnt; scalar_t__ pktsize; int /*<<< orphan*/  packet; struct hgpk_data* private; } ;
struct hgpk_data {scalar_t__ mode; scalar_t__ recalib_window; int /*<<< orphan*/  recalib_wq; } ;
typedef  int /*<<< orphan*/  psmouse_ret_t ;

/* Variables and functions */
 scalar_t__ HGPK_MODE_MOUSE ; 
 int /*<<< orphan*/  PSMOUSE_BAD_DATA ; 
 int /*<<< orphan*/  PSMOUSE_FULL_PACKET ; 
 int /*<<< orphan*/  PSMOUSE_GOOD_DATA ; 
 int /*<<< orphan*/  hgpk_is_byte_valid (struct psmouse*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hgpk_process_advanced_packet (struct psmouse*) ; 
 int /*<<< orphan*/  hgpk_process_simple_packet (struct psmouse*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  post_interrupt_delay ; 
 int /*<<< orphan*/  psmouse_dbg (struct psmouse*,char*) ; 
 int /*<<< orphan*/  psmouse_queue_work (struct psmouse*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static psmouse_ret_t hgpk_process_byte(struct psmouse *psmouse)
{
	struct hgpk_data *priv = psmouse->private;

	if (!hgpk_is_byte_valid(psmouse, psmouse->packet))
		return PSMOUSE_BAD_DATA;

	if (psmouse->pktcnt >= psmouse->pktsize) {
		if (priv->mode == HGPK_MODE_MOUSE)
			hgpk_process_simple_packet(psmouse);
		else
			hgpk_process_advanced_packet(psmouse);
		return PSMOUSE_FULL_PACKET;
	}

	if (priv->recalib_window) {
		if (time_before(jiffies, priv->recalib_window)) {
			/*
			 * ugh, got a packet inside our recalibration
			 * window, schedule another recalibration.
			 */
			psmouse_dbg(psmouse,
				    "packet inside calibration window, queueing another recalibration\n");
			psmouse_queue_work(psmouse, &priv->recalib_wq,
					msecs_to_jiffies(post_interrupt_delay));
		}
		priv->recalib_window = 0;
	}

	return PSMOUSE_GOOD_DATA;
}