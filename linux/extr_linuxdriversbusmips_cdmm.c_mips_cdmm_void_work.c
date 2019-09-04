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
struct mips_cdmm_work_dev {void (* fn ) (struct mips_cdmm_device*) ;struct mips_cdmm_device* dev; } ;

/* Variables and functions */

__attribute__((used)) static long mips_cdmm_void_work(void *data)
{
	struct mips_cdmm_work_dev *work = data;
	void (*fn)(struct mips_cdmm_device *) = work->fn;

	fn(work->dev);
	return 0;
}