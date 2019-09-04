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

void cxl_dump_debug_buffer(void *buf, size_t buf_len)
{
#ifdef DEBUG
	int i, *ptr;

	/*
	 * We want to regroup up to 4 integers per line, which means they
	 * need to be in the same pr_devel() statement
	 */
	ptr = (int *) buf;
	for (i = 0; i * 4 < buf_len; i += 4) {
		if ((i + 3) * 4 < buf_len)
			pr_devel("%.8x %.8x %.8x %.8x\n", ptr[i], ptr[i + 1],
				ptr[i + 2], ptr[i + 3]);
		else if ((i + 2) * 4 < buf_len)
			pr_devel("%.8x %.8x %.8x\n", ptr[i], ptr[i + 1],
				ptr[i + 2]);
		else if ((i + 1) * 4 < buf_len)
			pr_devel("%.8x %.8x\n", ptr[i], ptr[i + 1]);
		else
			pr_devel("%.8x\n", ptr[i]);
	}
#endif /* DEBUG */
}