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
struct map_info {int dummy; } ;
struct chip_probe {scalar_t__ (* probe_chip ) (struct map_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cfi_private*) ;} ;
struct cfi_private {int interleave; int device_type; } ;

/* Variables and functions */
 int CFI_DEVICETYPE_X32 ; 
 int /*<<< orphan*/  cfi_interleave_supported (int) ; 
 int map_bankwidth (struct map_info*) ; 
 scalar_t__ stub1 (struct map_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct cfi_private*) ; 

__attribute__((used)) static int genprobe_new_chip(struct map_info *map, struct chip_probe *cp,
			     struct cfi_private *cfi)
{
	int min_chips = (map_bankwidth(map)/4?:1); /* At most 4-bytes wide. */
	int max_chips = map_bankwidth(map); /* And minimum 1 */
	int nr_chips, type;

	for (nr_chips = max_chips; nr_chips >= min_chips; nr_chips >>= 1) {

		if (!cfi_interleave_supported(nr_chips))
		    continue;

		cfi->interleave = nr_chips;

		/* Minimum device size. Don't look for one 8-bit device
		   in a 16-bit bus, etc. */
		type = map_bankwidth(map) / nr_chips;

		for (; type <= CFI_DEVICETYPE_X32; type<<=1) {
			cfi->device_type = type;

			if (cp->probe_chip(map, 0, NULL, cfi))
				return 1;
		}
	}
	return 0;
}