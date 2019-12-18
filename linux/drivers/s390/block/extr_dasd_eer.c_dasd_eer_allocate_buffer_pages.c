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

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dasd_eer_free_buffer_pages (char**,int) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dasd_eer_allocate_buffer_pages(char **buf, int no_pages)
{
	int i;

	for (i = 0; i < no_pages; i++) {
		buf[i] = (char *) get_zeroed_page(GFP_KERNEL);
		if (!buf[i]) {
			dasd_eer_free_buffer_pages(buf, i);
			return -ENOMEM;
		}
	}
	return 0;
}