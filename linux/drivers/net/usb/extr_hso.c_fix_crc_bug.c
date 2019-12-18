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
typedef  int u32 ;
struct urb {int actual_length; scalar_t__ transfer_buffer; } ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcmp (int*,int const*,int) ; 

__attribute__((used)) static void fix_crc_bug(struct urb *urb, __le16 max_packet_size)
{
	static const u8 crc_check[4] = { 0xDE, 0xAD, 0xBE, 0xEF };
	u32 rest = urb->actual_length % le16_to_cpu(max_packet_size);

	if (((rest == 5) || (rest == 6)) &&
	    !memcmp(((u8 *)urb->transfer_buffer) + urb->actual_length - 4,
		    crc_check, 4)) {
		urb->actual_length -= 4;
	}
}