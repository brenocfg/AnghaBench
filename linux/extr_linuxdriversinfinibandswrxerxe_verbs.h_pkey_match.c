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
typedef  int u16 ;

/* Variables and functions */

__attribute__((used)) static inline int pkey_match(u16 key1, u16 key2)
{
	return (((key1 & 0x7fff) != 0) &&
		((key1 & 0x7fff) == (key2 & 0x7fff)) &&
		((key1 & 0x8000) || (key2 & 0x8000))) ? 1 : 0;
}