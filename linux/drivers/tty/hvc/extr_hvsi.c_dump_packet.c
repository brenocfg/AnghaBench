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
typedef  int /*<<< orphan*/  uint8_t ;
struct hvsi_header {int /*<<< orphan*/  len; int /*<<< orphan*/  seqno; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_hex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dump_packet(uint8_t *packet)
{
	struct hvsi_header *header = (struct hvsi_header *)packet;

	printk("type 0x%x, len %i, seqno %i:\n", header->type, header->len,
			header->seqno);

	dump_hex(packet, header->len);
}