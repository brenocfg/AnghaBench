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
typedef  int u64 ;
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline u64 encode_rcv_header_entry_size(u16 size)
{
	/* there are only 3 valid receive header entry sizes */
	if (size == 2)
		return 1;
	if (size == 16)
		return 2;
	else if (size == 32)
		return 4;
	return 0; /* invalid */
}