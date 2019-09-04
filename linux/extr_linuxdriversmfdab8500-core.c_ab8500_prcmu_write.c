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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct ab8500 {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int prcmu_abb_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int ab8500_prcmu_write(struct ab8500 *ab8500, u16 addr, u8 data)
{
	int ret;

	ret = prcmu_abb_write((u8)(addr >> 8), (u8)(addr & 0xFF), &data, 1);
	if (ret < 0)
		dev_err(ab8500->dev, "prcmu i2c error %d\n", ret);
	return ret;
}