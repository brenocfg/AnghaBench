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
struct cm_rep_msg {int offset26; } ;

/* Variables and functions */

__attribute__((used)) static inline void cm_rep_set_failover(struct cm_rep_msg *rep_msg, u8 failover)
{
	rep_msg->offset26 = (u8) ((rep_msg->offset26 & 0xF9) |
				  ((failover & 0x3) << 1));
}