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
struct packet_data {int state; } ;
typedef  enum packet_data_state { ____Placeholder_packet_data_state } packet_data_state ;

/* Variables and functions */

__attribute__((used)) static inline void pkt_set_state(struct packet_data *pkt, enum packet_data_state state)
{
#if PACKET_DEBUG > 1
	static const char *state_name[] = {
		"IDLE", "WAITING", "READ_WAIT", "WRITE_WAIT", "RECOVERY", "FINISHED"
	};
	enum packet_data_state old_state = pkt->state;
	pkt_dbg(2, pd, "pkt %2d : s=%6llx %s -> %s\n",
		pkt->id, (unsigned long long)pkt->sector,
		state_name[old_state], state_name[state]);
#endif
	pkt->state = state;
}