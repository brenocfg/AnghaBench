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
typedef  size_t u32 ;
struct venus_hfi_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  KERN_DEBUG ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,void const*,size_t,int) ; 
 int /*<<< orphan*/  venus_pkt_debug ; 

__attribute__((used)) static void venus_dump_packet(struct venus_hfi_device *hdev, const void *packet)
{
	size_t pkt_size = *(u32 *)packet;

	if (!venus_pkt_debug)
		return;

	print_hex_dump(KERN_DEBUG, "", DUMP_PREFIX_OFFSET, 16, 1, packet,
		       pkt_size, true);
}