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
typedef  int u8 ;
typedef  int u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct panfrost_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AS_COMMAND_LOCK ; 
 int /*<<< orphan*/  AS_LOCKADDR_HI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AS_LOCKADDR_LO (int /*<<< orphan*/ ) ; 
 int PAGE_MASK ; 
 size_t PAGE_SHIFT ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int fls (size_t) ; 
 int /*<<< orphan*/  mmu_write (struct panfrost_device*,int /*<<< orphan*/ ,int) ; 
 size_t round_up (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_cmd (struct panfrost_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lock_region(struct panfrost_device *pfdev, u32 as_nr,
			u64 iova, size_t size)
{
	u8 region_width;
	u64 region = iova & PAGE_MASK;
	/*
	 * fls returns:
	 * 1 .. 32
	 *
	 * 10 + fls(num_pages)
	 * results in the range (11 .. 42)
	 */

	size = round_up(size, PAGE_SIZE);

	region_width = 10 + fls(size >> PAGE_SHIFT);
	if ((size >> PAGE_SHIFT) != (1ul << (region_width - 11))) {
		/* not pow2, so must go up to the next pow2 */
		region_width += 1;
	}
	region |= region_width;

	/* Lock the region that needs to be updated */
	mmu_write(pfdev, AS_LOCKADDR_LO(as_nr), region & 0xFFFFFFFFUL);
	mmu_write(pfdev, AS_LOCKADDR_HI(as_nr), (region >> 32) & 0xFFFFFFFFUL);
	write_cmd(pfdev, as_nr, AS_COMMAND_LOCK);
}