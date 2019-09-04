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
typedef  int /*<<< orphan*/  dm_cblock_t ;

/* Variables and functions */
 int NR_CACHE_LEVELS ; 
 int /*<<< orphan*/  from_cblock (int /*<<< orphan*/ ) ; 
 int hash_32 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned random_level(dm_cblock_t cblock)
{
	return hash_32(from_cblock(cblock), 9) & (NR_CACHE_LEVELS - 1);
}