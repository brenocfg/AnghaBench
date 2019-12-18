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
struct mon_msg {int mca_offset; } ;

/* Variables and functions */
 scalar_t__ mon_mca_start (struct mon_msg*) ; 

__attribute__((used)) static inline u8 mon_mca_type(struct mon_msg *monmsg, u8 index)
{
	return *((u8 *) mon_mca_start(monmsg) + monmsg->mca_offset + index);
}