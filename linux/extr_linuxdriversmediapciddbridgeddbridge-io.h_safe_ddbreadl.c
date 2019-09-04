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
typedef  int /*<<< orphan*/  u32 ;
struct ddb {TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ddbreadl (struct ddb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u32 safe_ddbreadl(struct ddb *dev, u32 adr)
{
	u32 val = ddbreadl(dev, adr);

	/* (ddb)readl returns (uint)-1 (all bits set) on failure, catch that */
	if (val == ~0) {
		dev_err(&dev->pdev->dev, "ddbreadl failure, adr=%08x\n", adr);
		return 0;
	}

	return val;
}