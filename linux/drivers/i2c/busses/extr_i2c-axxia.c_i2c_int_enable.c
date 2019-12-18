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
typedef  int u32 ;
struct axxia_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ MST_INT_ENABLE ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void i2c_int_enable(struct axxia_i2c_dev *idev, u32 mask)
{
	u32 int_en;

	int_en = readl(idev->base + MST_INT_ENABLE);
	writel(int_en | mask, idev->base + MST_INT_ENABLE);
}