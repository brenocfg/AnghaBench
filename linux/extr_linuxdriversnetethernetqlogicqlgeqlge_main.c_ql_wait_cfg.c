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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG ; 
 int CFG_LE ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int UDELAY_COUNT ; 
 int /*<<< orphan*/  UDELAY_DELAY ; 
 int ql_read32 (struct ql_adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ql_wait_cfg(struct ql_adapter *qdev, u32 bit)
{
	int count = UDELAY_COUNT;
	u32 temp;

	while (count) {
		temp = ql_read32(qdev, CFG);
		if (temp & CFG_LE)
			return -EIO;
		if (!(temp & bit))
			return 0;
		udelay(UDELAY_DELAY);
		count--;
	}
	return -ETIMEDOUT;
}