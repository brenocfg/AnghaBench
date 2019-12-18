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

/* Variables and functions */
 int /*<<< orphan*/  VMW_TRY_FIND_FIRST_DIFF (int /*<<< orphan*/ ) ; 
 size_t round_down (scalar_t__,size_t) ; 
 int /*<<< orphan*/  u16 ; 
 int /*<<< orphan*/  u32 ; 
 int /*<<< orphan*/  u64 ; 
 scalar_t__ vmw_find_first_diff_u8 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,size_t) ; 

__attribute__((used)) static size_t vmw_find_first_diff(const u8 *dst, const u8 *src, size_t size,
				  size_t granularity)
{
	size_t offset = 0;

	/*
	 * Try finding with large integers if alignment allows, or we can
	 * fix it. Fall through if we need better resolution or alignment
	 * was bad.
	 */
#ifdef CONFIG_64BIT
	VMW_TRY_FIND_FIRST_DIFF(u64);
#endif
	VMW_TRY_FIND_FIRST_DIFF(u32);
	VMW_TRY_FIND_FIRST_DIFF(u16);

	return round_down(offset + vmw_find_first_diff_u8(dst, src, size),
			  granularity);
}