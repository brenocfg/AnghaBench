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
struct bcm_kona_i2c_dev {scalar_t__ base; } ;

/* Variables and functions */
 int CLKEN_AUTOSENSE_OFF_MASK ; 
 scalar_t__ CLKEN_OFFSET ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void bcm_kona_i2c_enable_autosense(struct bcm_kona_i2c_dev *dev)
{
	writel(readl(dev->base + CLKEN_OFFSET) & ~CLKEN_AUTOSENSE_OFF_MASK,
	       dev->base + CLKEN_OFFSET);
}