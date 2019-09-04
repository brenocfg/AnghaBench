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
struct mcba_usb_msg_ka_can {int /*<<< orphan*/  can_bitrate; } ;

/* Variables and functions */
 int get_unaligned_be16 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 convert_can2host_bitrate(struct mcba_usb_msg_ka_can *msg)
{
	const u32 bitrate = get_unaligned_be16(&msg->can_bitrate);

	if ((bitrate == 33) || (bitrate == 83))
		return bitrate * 1000 + 333;
	else
		return bitrate * 1000;
}