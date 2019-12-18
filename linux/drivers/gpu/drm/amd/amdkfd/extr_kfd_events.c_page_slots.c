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
typedef  int /*<<< orphan*/  uint64_t ;
struct kfd_signal_page {int /*<<< orphan*/ * kernel_address; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t *page_slots(struct kfd_signal_page *page)
{
	return page->kernel_address;
}