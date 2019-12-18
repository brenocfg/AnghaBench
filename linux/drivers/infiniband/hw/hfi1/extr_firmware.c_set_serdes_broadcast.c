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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_SBUS_RECEIVER ; 
 int /*<<< orphan*/  sbus_request (struct hfi1_devdata*,scalar_t__ const,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void set_serdes_broadcast(struct hfi1_devdata *dd, u8 bg1, u8 bg2,
				 const u8 *addrs, int count)
{
	while (--count >= 0) {
		/*
		 * Set BROADCAST_GROUP_1 and BROADCAST_GROUP_2, leave
		 * defaults for everything else.  Do not read-modify-write,
		 * per instruction from the manufacturer.
		 *
		 * Register 0xfd:
		 *	bits    what
		 *	-----	---------------------------------
		 *	  0	IGNORE_BROADCAST  (default 0)
		 *	11:4	BROADCAST_GROUP_1 (default 0xff)
		 *	23:16	BROADCAST_GROUP_2 (default 0xff)
		 */
		sbus_request(dd, addrs[count], 0xfd, WRITE_SBUS_RECEIVER,
			     (u32)bg1 << 4 | (u32)bg2 << 16);
	}
}