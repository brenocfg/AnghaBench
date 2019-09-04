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
struct skd_device {int dbg_level; TYPE_1__* pdev; scalar_t__* mem_map; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writel (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void skd_reg_write32(struct skd_device *skdev, u32 val,
				   u32 offset)
{
	writel(val, skdev->mem_map[1] + offset);
	if (unlikely(skdev->dbg_level >= 2))
		dev_dbg(&skdev->pdev->dev, "offset %x = %x\n", offset, val);
}