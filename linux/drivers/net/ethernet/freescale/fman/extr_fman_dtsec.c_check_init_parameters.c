#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fman_mac {scalar_t__ max_speed; scalar_t__ addr; int /*<<< orphan*/  event_cb; int /*<<< orphan*/  exception_cb; TYPE_1__* dtsec_drv_param; } ;
struct TYPE_2__ {scalar_t__ rx_prepend; scalar_t__ non_back_to_back_ipg1; scalar_t__ non_back_to_back_ipg2; scalar_t__ back_to_back_ipg; scalar_t__ halfdup_retransmit; scalar_t__ halfdup_coll_window; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_COLLISION_WINDOW ; 
 scalar_t__ MAX_INTER_PACKET_GAP ; 
 scalar_t__ MAX_PACKET_ALIGNMENT ; 
 scalar_t__ MAX_RETRANSMISSION ; 
 scalar_t__ SPEED_10000 ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

__attribute__((used)) static int check_init_parameters(struct fman_mac *dtsec)
{
	if (dtsec->max_speed >= SPEED_10000) {
		pr_err("1G MAC driver supports 1G or lower speeds\n");
		return -EINVAL;
	}
	if (dtsec->addr == 0) {
		pr_err("Ethernet MAC Must have a valid MAC Address\n");
		return -EINVAL;
	}
	if ((dtsec->dtsec_drv_param)->rx_prepend >
	    MAX_PACKET_ALIGNMENT) {
		pr_err("packetAlignmentPadding can't be > than %d\n",
		       MAX_PACKET_ALIGNMENT);
		return -EINVAL;
	}
	if (((dtsec->dtsec_drv_param)->non_back_to_back_ipg1 >
	     MAX_INTER_PACKET_GAP) ||
	    ((dtsec->dtsec_drv_param)->non_back_to_back_ipg2 >
	     MAX_INTER_PACKET_GAP) ||
	     ((dtsec->dtsec_drv_param)->back_to_back_ipg >
	      MAX_INTER_PACKET_GAP)) {
		pr_err("Inter packet gap can't be greater than %d\n",
		       MAX_INTER_PACKET_GAP);
		return -EINVAL;
	}
	if ((dtsec->dtsec_drv_param)->halfdup_retransmit >
	    MAX_RETRANSMISSION) {
		pr_err("maxRetransmission can't be greater than %d\n",
		       MAX_RETRANSMISSION);
		return -EINVAL;
	}
	if ((dtsec->dtsec_drv_param)->halfdup_coll_window >
	    MAX_COLLISION_WINDOW) {
		pr_err("collisionWindow can't be greater than %d\n",
		       MAX_COLLISION_WINDOW);
		return -EINVAL;
	/* If Auto negotiation process is disabled, need to set up the PHY
	 * using the MII Management Interface
	 */
	}
	if (!dtsec->exception_cb) {
		pr_err("uninitialized exception_cb\n");
		return -EINVAL;
	}
	if (!dtsec->event_cb) {
		pr_err("uninitialized event_cb\n");
		return -EINVAL;
	}

	return 0;
}