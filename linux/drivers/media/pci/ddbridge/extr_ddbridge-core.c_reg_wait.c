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
struct ddb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ndelay (int) ; 
 int safe_ddbreadl (struct ddb*,int) ; 

__attribute__((used)) static int reg_wait(struct ddb *dev, u32 reg, u32 bit)
{
	u32 count = 0;

	while (safe_ddbreadl(dev, reg) & bit) {
		ndelay(10);
		if (++count == 100)
			return -1;
	}
	return 0;
}