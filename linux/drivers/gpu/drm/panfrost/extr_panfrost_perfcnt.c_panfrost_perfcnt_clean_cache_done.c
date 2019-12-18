#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct panfrost_device {TYPE_1__* perfcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  dump_comp; } ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

void panfrost_perfcnt_clean_cache_done(struct panfrost_device *pfdev)
{
	complete(&pfdev->perfcnt->dump_comp);
}