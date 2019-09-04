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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct alx_hw {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  ALX_STAD0 ; 
 int /*<<< orphan*/  ALX_STAD1 ; 
 int /*<<< orphan*/  alx_write_mem32 (struct alx_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_unaligned (int /*<<< orphan*/ *) ; 

void alx_set_macaddr(struct alx_hw *hw, const u8 *addr)
{
	u32 val;

	/* for example: 00-0B-6A-F6-00-DC * STAD0=6AF600DC, STAD1=000B */
	val = be32_to_cpu(get_unaligned((__be32 *)(addr + 2)));
	alx_write_mem32(hw, ALX_STAD0, val);
	val = be16_to_cpu(get_unaligned((__be16 *)addr));
	alx_write_mem32(hw, ALX_STAD1, val);
}