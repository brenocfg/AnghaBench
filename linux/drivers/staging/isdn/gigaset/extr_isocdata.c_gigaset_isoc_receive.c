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
struct bc_state {int proto2; } ;

/* Variables and functions */
#define  L2_HDLC 128 
 int /*<<< orphan*/  hdlc_unpack (unsigned char*,unsigned int,struct bc_state*) ; 
 int /*<<< orphan*/  trans_receive (unsigned char*,unsigned int,struct bc_state*) ; 

void gigaset_isoc_receive(unsigned char *src, unsigned count,
			  struct bc_state *bcs)
{
	switch (bcs->proto2) {
	case L2_HDLC:
		hdlc_unpack(src, count, bcs);
		break;
	default:		/* assume transparent */
		trans_receive(src, count, bcs);
	}
}