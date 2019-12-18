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
struct pmem_device {int /*<<< orphan*/  disk; int /*<<< orphan*/  dax_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill_dax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_dax (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pmem_release_disk(void *__pmem)
{
	struct pmem_device *pmem = __pmem;

	kill_dax(pmem->dax_dev);
	put_dax(pmem->dax_dev);
	del_gendisk(pmem->disk);
	put_disk(pmem->disk);
}