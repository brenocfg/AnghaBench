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
typedef  int u32 ;

/* Variables and functions */
 int crc32c (int,void const*,size_t) ; 

u32 dm_bm_checksum(const void *data, size_t len, u32 init_xor)
{
	return crc32c(~(u32) 0, data, len) ^ init_xor;
}