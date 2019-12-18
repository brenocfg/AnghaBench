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
typedef  int u_int32_t ;
struct aac_dev {scalar_t__ base; } ;

/* Variables and functions */
 int IBW_SWR_OFFSET ; 
 int /*<<< orphan*/  aac_clear_omr (struct aac_dev*) ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int readl (char*) ; 
 int /*<<< orphan*/  writel (int,char*) ; 

__attribute__((used)) static void aac_send_hardware_soft_reset(struct aac_dev *dev)
{
	u_int32_t val;

	aac_clear_omr(dev);
	val = readl(((char *)(dev->base) + IBW_SWR_OFFSET));
	val |= 0x01;
	writel(val, ((char *)(dev->base) + IBW_SWR_OFFSET));
	msleep_interruptible(20000);
}