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
typedef  int uint8_t ;

/* Variables and functions */

__attribute__((used)) static inline int
aes_hw_extkey_available(uint8_t key_len)
{
	/* TODO: We should check the actual CPU model/stepping
	         as it's possible that the capability will be
	         added in the next CPU revisions. */
	if (key_len == 16)
		return 1;
	return 0;
}