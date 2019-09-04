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
struct pt1 {int dummy; } ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  pt1_i2c_emit (struct pt1*,int,int,int /*<<< orphan*/ ,int,int,int) ; 
 int pt1_read_reg (struct pt1*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pt1_write_reg (struct pt1*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int pt1_i2c_end(struct pt1 *pt1, int addr)
{
	pt1_i2c_emit(pt1, addr,     1, 0, 0, 0, addr + 1);
	pt1_i2c_emit(pt1, addr + 1, 1, 0, 1, 0, addr + 2);
	pt1_i2c_emit(pt1, addr + 2, 1, 0, 1, 1, 0);

	pt1_write_reg(pt1, 0, 0x00000004);
	do {
		if (signal_pending(current))
			return -EINTR;
		usleep_range(1000, 2000);
	} while (pt1_read_reg(pt1, 0) & 0x00000080);
	return 0;
}