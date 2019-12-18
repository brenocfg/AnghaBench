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
struct pt1 {int i2c_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  pt1_i2c_emit (struct pt1*,int,int,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void pt1_i2c_begin(struct pt1 *pt1, int *addrp)
{
	int addr;
	addr = 0;

	pt1_i2c_emit(pt1, addr,     0, 0, 1, 1, addr /* itself */);
	addr = addr + 1;

	if (!pt1->i2c_running) {
		pt1_i2c_emit(pt1, addr,     1, 0, 1, 1, addr + 1);
		pt1_i2c_emit(pt1, addr + 1, 1, 0, 1, 0, addr + 2);
		addr = addr + 2;
		pt1->i2c_running = 1;
	}
	*addrp = addr;
}