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
struct ttm_mem_reg {int dummy; } ;
struct ttm_bo_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void cirrus_ttm_io_mem_free(struct ttm_bo_device *bdev, struct ttm_mem_reg *mem)
{
}