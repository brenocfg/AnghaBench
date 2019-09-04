#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int start; int end; int /*<<< orphan*/  buffer_addr; int /*<<< orphan*/  num_bytes; } ;
struct biosmemcon_ebda {TYPE_1__ v2; } ;

/* Variables and functions */
 int /*<<< orphan*/  memconsole_baseaddr ; 
 int memconsole_length ; 
 int /*<<< orphan*/  memconsole_read ; 
 int /*<<< orphan*/  memconsole_setup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phys_to_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,struct biosmemcon_ebda*,...) ; 

__attribute__((used)) static void found_v2_header(struct biosmemcon_ebda *hdr)
{
	pr_info("memconsole: BIOS console v2 EBDA structure found at %p\n",
		hdr);
	pr_info("memconsole: BIOS console buffer at 0x%.8x, start = %d, end = %d, num_bytes = %d\n",
		hdr->v2.buffer_addr, hdr->v2.start,
		hdr->v2.end, hdr->v2.num_bytes);

	memconsole_baseaddr = phys_to_virt(hdr->v2.buffer_addr + hdr->v2.start);
	memconsole_length = hdr->v2.end - hdr->v2.start;
	memconsole_setup(memconsole_read);
}