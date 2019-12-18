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
typedef  int u8 ;
struct cm_lap_msg {int offset61; } ;

/* Variables and functions */

__attribute__((used)) static inline void cm_lap_set_packet_rate(struct cm_lap_msg *lap_msg,
					  u8 packet_rate)
{
	lap_msg->offset61 = (packet_rate & 0x3F) | (lap_msg->offset61 & 0xC0);
}