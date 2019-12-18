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
struct dm_target {int dummy; } ;
struct dm_dev {int /*<<< orphan*/  bdev; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int BDEVNAME_SIZE ; 
 int /*<<< orphan*/  bdevname (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int device_no_partial_completion(struct dm_target *ti, struct dm_dev *dev,
					sector_t start, sector_t len, void *data)
{
	char b[BDEVNAME_SIZE];

	/* For now, NVMe devices are the only devices of this class */
	return (strncmp(bdevname(dev->bdev, b), "nvme", 4) == 0);
}