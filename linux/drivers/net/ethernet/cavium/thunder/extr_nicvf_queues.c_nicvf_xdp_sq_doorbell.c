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
struct snd_queue {scalar_t__ xdp_desc_cnt; } ;
struct nicvf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NIC_QSET_SQ_0_7_DOOR ; 
 int /*<<< orphan*/  nicvf_queue_reg_write (struct nicvf*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  wmb () ; 

void nicvf_xdp_sq_doorbell(struct nicvf *nic,
			   struct snd_queue *sq, int sq_num)
{
	if (!sq->xdp_desc_cnt)
		return;

	/* make sure all memory stores are done before ringing doorbell */
	wmb();

	/* Inform HW to xmit all TSO segments */
	nicvf_queue_reg_write(nic, NIC_QSET_SQ_0_7_DOOR,
			      sq_num, sq->xdp_desc_cnt);
	sq->xdp_desc_cnt = 0;
}