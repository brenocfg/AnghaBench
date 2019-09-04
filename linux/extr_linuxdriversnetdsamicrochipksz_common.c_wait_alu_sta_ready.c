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
struct ksz_device {int dummy; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  REG_SW_ALU_STAT_CTRL__4 ; 
 int /*<<< orphan*/  ksz_read32 (struct ksz_device*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int wait_alu_sta_ready(struct ksz_device *dev, u32 waiton, int timeout)
{
	u32 data;

	do {
		ksz_read32(dev, REG_SW_ALU_STAT_CTRL__4, &data);
		if (!(data & waiton))
			break;
		usleep_range(1, 10);
	} while (timeout-- > 0);

	if (timeout <= 0)
		return -ETIMEDOUT;

	return 0;
}