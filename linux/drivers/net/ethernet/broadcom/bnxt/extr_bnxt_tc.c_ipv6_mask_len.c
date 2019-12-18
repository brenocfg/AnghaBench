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
struct in6_addr {int /*<<< orphan*/ * s6_addr32; } ;

/* Variables and functions */
 scalar_t__ inet_mask_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ipv6_mask_len(struct in6_addr *mask)
{
	int mask_len = 0, i;

	for (i = 0; i < 4; i++)
		mask_len += inet_mask_len(mask->s6_addr32[i]);

	return mask_len;
}