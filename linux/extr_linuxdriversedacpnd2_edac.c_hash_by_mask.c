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

/* Variables and functions */

__attribute__((used)) static int hash_by_mask(u64 addr, u64 mask)
{
	u64 result = addr & mask;

	result = (result >> 32) ^ result;
	result = (result >> 16) ^ result;
	result = (result >> 8) ^ result;
	result = (result >> 4) ^ result;
	result = (result >> 2) ^ result;
	result = (result >> 1) ^ result;

	return (int)result & 1;
}