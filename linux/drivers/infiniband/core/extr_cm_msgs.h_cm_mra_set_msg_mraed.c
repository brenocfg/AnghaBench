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
struct cm_mra_msg {int offset8; } ;

/* Variables and functions */

__attribute__((used)) static inline void cm_mra_set_msg_mraed(struct cm_mra_msg *mra_msg, u8 msg)
{
	mra_msg->offset8 = (u8) ((mra_msg->offset8 & 0x3F) | (msg << 6));
}