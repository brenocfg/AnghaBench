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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  __u32 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32p (int /*<<< orphan*/  const*) ; 

void qce_cpu_to_be32p_array(__be32 *dst, const u8 *src, unsigned int len)
{
	__be32 *d = dst;
	const u8 *s = src;
	unsigned int n;

	n = len / sizeof(u32);
	for (; n > 0; n--) {
		*d = cpu_to_be32p((const __u32 *) s);
		s += sizeof(__u32);
		d++;
	}
}