#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct ilo_hwinfo {int dummy; } ;
struct TYPE_8__ {char* recv_desc; } ;
struct TYPE_7__ {char* recv_fifobar; } ;
struct TYPE_6__ {char* send_desc; } ;
struct TYPE_5__ {char* send_fifobar; } ;
struct ccb {TYPE_4__ ccb_u4; TYPE_3__ ccb_u3; TYPE_2__ ccb_u2; TYPE_1__ ccb_u1; } ;

/* Variables and functions */
 int SENDQ ; 
 int desc_mem_sz (int) ; 
 int fifo_dequeue (struct ilo_hwinfo*,char*,int*) ; 
 int get_entry_id (int) ; 
 int get_entry_len (int) ; 

__attribute__((used)) static int ilo_pkt_dequeue(struct ilo_hwinfo *hw, struct ccb *ccb,
			   int dir, int *id, int *len, void **pkt)
{
	char *fifobar, *desc;
	int entry = 0, pkt_id = 0;
	int ret;

	if (dir == SENDQ) {
		fifobar = ccb->ccb_u1.send_fifobar;
		desc = ccb->ccb_u2.send_desc;
	} else {
		fifobar = ccb->ccb_u3.recv_fifobar;
		desc = ccb->ccb_u4.recv_desc;
	}

	ret = fifo_dequeue(hw, fifobar, &entry);
	if (ret) {
		pkt_id = get_entry_id(entry);
		if (id)
			*id = pkt_id;
		if (len)
			*len = get_entry_len(entry);
		if (pkt)
			*pkt = (void *)(desc + desc_mem_sz(pkt_id));
	}

	return ret;
}