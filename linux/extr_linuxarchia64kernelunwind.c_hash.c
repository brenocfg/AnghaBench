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
typedef  unsigned long unw_hash_index_t ;

/* Variables and functions */
 int UNW_LOG_HASH_SIZE ; 

__attribute__((used)) static inline unw_hash_index_t
hash (unsigned long ip)
{
	/* magic number = ((sqrt(5)-1)/2)*2^64 */
	static const unsigned long hashmagic = 0x9e3779b97f4a7c16UL;

	return (ip >> 4) * hashmagic >> (64 - UNW_LOG_HASH_SIZE);
}