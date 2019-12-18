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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  gcr_lock; scalar_t__ gcr_mem_base; } ;

/* Variables and functions */
 TYPE_1__ ipcdev ; 
 int is_gcr_valid (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

int intel_pmc_gcr_write(u32 offset, u32 data)
{
	int ret;

	spin_lock(&ipcdev.gcr_lock);

	ret = is_gcr_valid(offset);
	if (ret < 0) {
		spin_unlock(&ipcdev.gcr_lock);
		return ret;
	}

	writel(data, ipcdev.gcr_mem_base + offset);

	spin_unlock(&ipcdev.gcr_lock);

	return 0;
}