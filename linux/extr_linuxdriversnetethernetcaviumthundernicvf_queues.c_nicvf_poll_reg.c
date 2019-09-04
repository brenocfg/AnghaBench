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
typedef  int u64 ;
struct nicvf {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int) ; 
 int nicvf_queue_reg_read (struct nicvf*,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int nicvf_poll_reg(struct nicvf *nic, int qidx,
			  u64 reg, int bit_pos, int bits, int val)
{
	u64 bit_mask;
	u64 reg_val;
	int timeout = 10;

	bit_mask = (1ULL << bits) - 1;
	bit_mask = (bit_mask << bit_pos);

	while (timeout) {
		reg_val = nicvf_queue_reg_read(nic, reg, qidx);
		if (((reg_val & bit_mask) >> bit_pos) == val)
			return 0;
		usleep_range(1000, 2000);
		timeout--;
	}
	netdev_err(nic->netdev, "Poll on reg 0x%llx failed\n", reg);
	return 1;
}