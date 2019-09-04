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
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void create_last_hash_block(char *bfr_ptr, unsigned int bs, u64 scmd1)
{
	memset(bfr_ptr, 0, bs);
	*bfr_ptr = 0x80;
	if (bs == 64)
		*(__be64 *)(bfr_ptr + 56) = cpu_to_be64(scmd1  << 3);
	else
		*(__be64 *)(bfr_ptr + 120) =  cpu_to_be64(scmd1  << 3);
}