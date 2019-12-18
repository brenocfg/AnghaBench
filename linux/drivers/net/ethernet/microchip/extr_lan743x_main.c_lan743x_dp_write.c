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
struct lan743x_adapter {int /*<<< orphan*/  dp_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ADDR ; 
 int /*<<< orphan*/  DP_CMD ; 
 int DP_CMD_WRITE_ ; 
 int /*<<< orphan*/  DP_DATA_0 ; 
 int /*<<< orphan*/  DP_SEL ; 
 int /*<<< orphan*/  DP_SEL_DPRDY_ ; 
 int DP_SEL_MASK_ ; 
 int EIO ; 
 int lan743x_csr_read (struct lan743x_adapter*,int /*<<< orphan*/ ) ; 
 scalar_t__ lan743x_csr_wait_for_bit (struct lan743x_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  lan743x_csr_write (struct lan743x_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lan743x_dp_write(struct lan743x_adapter *adapter,
			    u32 select, u32 addr, u32 length, u32 *buf)
{
	int ret = -EIO;
	u32 dp_sel;
	int i;

	mutex_lock(&adapter->dp_lock);
	if (lan743x_csr_wait_for_bit(adapter, DP_SEL, DP_SEL_DPRDY_,
				     1, 40, 100, 100))
		goto unlock;
	dp_sel = lan743x_csr_read(adapter, DP_SEL);
	dp_sel &= ~DP_SEL_MASK_;
	dp_sel |= select;
	lan743x_csr_write(adapter, DP_SEL, dp_sel);

	for (i = 0; i < length; i++) {
		lan743x_csr_write(adapter, DP_ADDR, addr + i);
		lan743x_csr_write(adapter, DP_DATA_0, buf[i]);
		lan743x_csr_write(adapter, DP_CMD, DP_CMD_WRITE_);
		if (lan743x_csr_wait_for_bit(adapter, DP_SEL, DP_SEL_DPRDY_,
					     1, 40, 100, 100))
			goto unlock;
	}
	ret = 0;

unlock:
	mutex_unlock(&adapter->dp_lock);
	return ret;
}