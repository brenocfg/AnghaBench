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
struct cm_lap_msg {int offset63; } ;

/* Variables and functions */

__attribute__((used)) static inline void cm_lap_set_local_ack_timeout(struct cm_lap_msg *lap_msg,
						u8 local_ack_timeout)
{
	lap_msg->offset63 = (local_ack_timeout << 3) |
			    (lap_msg->offset63 & 0x07);
}