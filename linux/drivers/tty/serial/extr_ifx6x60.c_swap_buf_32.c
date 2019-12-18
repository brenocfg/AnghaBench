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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline void swap_buf_32(unsigned char *buf, int len, void *end)
{
	int n;

	u32 *buf_32 = (u32 *)buf;
	len = (len + 3) >> 2;

	if ((void *)&buf_32[len] > end) {
		pr_err("swap_buf_32: swap exceeds boundary (%p > %p)!\n",
		       &buf_32[len], end);
		return;
	}
	for (n = 0; n < len; n++) {
		*buf_32 = cpu_to_be32(*buf_32);
		buf_32++;
	}
}