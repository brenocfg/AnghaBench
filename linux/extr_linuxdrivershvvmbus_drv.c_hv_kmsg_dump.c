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
struct kmsg_dumper {int dummy; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
typedef  enum kmsg_dump_reason { ____Placeholder_kmsg_dump_reason } kmsg_dump_reason ;

/* Variables and functions */
 int KMSG_DUMP_PANIC ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  hv_panic_page ; 
 int /*<<< orphan*/  hyperv_report_panic_msg (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  kmsg_dump_get_buffer (struct kmsg_dumper*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t*) ; 
 int /*<<< orphan*/  sysctl_record_panic_msg ; 
 int /*<<< orphan*/  virt_to_phys (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hv_kmsg_dump(struct kmsg_dumper *dumper,
			 enum kmsg_dump_reason reason)
{
	size_t bytes_written;
	phys_addr_t panic_pa;

	/* We are only interested in panics. */
	if ((reason != KMSG_DUMP_PANIC) || (!sysctl_record_panic_msg))
		return;

	panic_pa = virt_to_phys(hv_panic_page);

	/*
	 * Write dump contents to the page. No need to synchronize; panic should
	 * be single-threaded.
	 */
	kmsg_dump_get_buffer(dumper, true, hv_panic_page, PAGE_SIZE,
			     &bytes_written);
	if (bytes_written)
		hyperv_report_panic_msg(panic_pa, bytes_written);
}