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
typedef  int /*<<< orphan*/  u64 ;
struct vas_window {int /*<<< orphan*/ * paste_addr_name; int /*<<< orphan*/ * paste_kaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  compute_paste_address (struct vas_window*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unmap_region (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void unmap_paste_region(struct vas_window *window)
{
	int len;
	u64 busaddr_start;

	if (window->paste_kaddr) {
		compute_paste_address(window, &busaddr_start, &len);
		unmap_region(window->paste_kaddr, busaddr_start, len);
		window->paste_kaddr = NULL;
		kfree(window->paste_addr_name);
		window->paste_addr_name = NULL;
	}
}