#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct ubi_device {TYPE_1__* mtd; } ;
struct TYPE_4__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int mtd_div_by_eb (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  mtd_get_device_size (TYPE_1__*) ; 
 int mtd_max_bad_blocks (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mult_frac (int,int,int) ; 

__attribute__((used)) static int get_bad_peb_limit(const struct ubi_device *ubi, int max_beb_per1024)
{
	int limit, device_pebs;
	uint64_t device_size;

	if (!max_beb_per1024) {
		/*
		 * Since max_beb_per1024 has not been set by the user in either
		 * the cmdline or Kconfig, use mtd_max_bad_blocks to set the
		 * limit if it is supported by the device.
		 */
		limit = mtd_max_bad_blocks(ubi->mtd, 0, ubi->mtd->size);
		if (limit < 0)
			return 0;
		return limit;
	}

	/*
	 * Here we are using size of the entire flash chip and
	 * not just the MTD partition size because the maximum
	 * number of bad eraseblocks is a percentage of the
	 * whole device and bad eraseblocks are not fairly
	 * distributed over the flash chip. So the worst case
	 * is that all the bad eraseblocks of the chip are in
	 * the MTD partition we are attaching (ubi->mtd).
	 */
	device_size = mtd_get_device_size(ubi->mtd);
	device_pebs = mtd_div_by_eb(device_size, ubi->mtd);
	limit = mult_frac(device_pebs, max_beb_per1024, 1024);

	/* Round it up */
	if (mult_frac(limit, 1024, max_beb_per1024) < device_pebs)
		limit += 1;

	return limit;
}