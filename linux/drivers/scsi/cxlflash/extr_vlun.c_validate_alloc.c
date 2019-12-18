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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u64 ;
struct ba_lun_info {int /*<<< orphan*/ * lun_alloc_map; } ;

/* Variables and functions */
 int BITS_PER_LONG ; 
 scalar_t__ test_bit (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int validate_alloc(struct ba_lun_info *bali, u64 aun)
{
	int idx = 0, bit_pos = 0;

	idx = aun / BITS_PER_LONG;
	bit_pos = aun % BITS_PER_LONG;

	if (test_bit(bit_pos, (ulong *)&bali->lun_alloc_map[idx]))
		return -1;

	return 0;
}