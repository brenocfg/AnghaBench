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
typedef  int u32 ;

/* Variables and functions */
#define  SELFID_PORT_CHILD 131 
#define  SELFID_PORT_NCONN 130 
#define  SELFID_PORT_NONE 129 
#define  SELFID_PORT_PARENT 128 
 int /*<<< orphan*/  SELF_ID_EXTENDED (int) ; 
 int SELF_ID_EXT_SEQUENCE (int) ; 
 int /*<<< orphan*/  SELF_ID_MORE_PACKETS (int) ; 

__attribute__((used)) static u32 *count_ports(u32 *sid, int *total_port_count, int *child_port_count)
{
	u32 q;
	int port_type, shift, seq;

	*total_port_count = 0;
	*child_port_count = 0;

	shift = 6;
	q = *sid;
	seq = 0;

	while (1) {
		port_type = (q >> shift) & 0x03;
		switch (port_type) {
		case SELFID_PORT_CHILD:
			(*child_port_count)++;
		case SELFID_PORT_PARENT:
		case SELFID_PORT_NCONN:
			(*total_port_count)++;
		case SELFID_PORT_NONE:
			break;
		}

		shift -= 2;
		if (shift == 0) {
			if (!SELF_ID_MORE_PACKETS(q))
				return sid + 1;

			shift = 16;
			sid++;
			q = *sid;

			/*
			 * Check that the extra packets actually are
			 * extended self ID packets and that the
			 * sequence numbers in the extended self ID
			 * packets increase as expected.
			 */

			if (!SELF_ID_EXTENDED(q) ||
			    seq != SELF_ID_EXT_SEQUENCE(q))
				return NULL;

			seq++;
		}
	}
}