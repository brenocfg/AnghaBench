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
struct lan743x_adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LAN743X_CSR_READ_OP ; 
 int readx_poll_timeout (int /*<<< orphan*/ ,int,int,int,int,int) ; 

__attribute__((used)) static int lan743x_csr_wait_for_bit(struct lan743x_adapter *adapter,
				    int offset, u32 bit_mask,
				    int target_value, int usleep_min,
				    int usleep_max, int count)
{
	u32 data;

	return readx_poll_timeout(LAN743X_CSR_READ_OP, offset, data,
				  target_value == ((data & bit_mask) ? 1 : 0),
				  usleep_max, usleep_min * count);
}