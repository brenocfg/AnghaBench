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
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline void swap_buf_16(unsigned char *buf, int len, void *end)
{
	int n;

	u16 *buf_16 = (u16 *)buf;
	len = ((len + 1) >> 1);
	if ((void *)&buf_16[len] > end) {
		pr_err("swap_buf_16: swap exceeds boundary (%p > %p)!",
		       &buf_16[len], end);
		return;
	}
	for (n = 0; n < len; n++) {
		*buf_16 = cpu_to_be16(*buf_16);
		buf_16++;
	}
}