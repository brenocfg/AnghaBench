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
struct freelQ_e {int len_gen; int /*<<< orphan*/  gen2; int /*<<< orphan*/  addr_hi; int /*<<< orphan*/  addr_lo; } ;
struct freelQ {size_t pidx; int genbit; size_t size; int /*<<< orphan*/  credits; int /*<<< orphan*/ * centries; struct freelQ_e* entries; } ;

/* Variables and functions */
 int G_CMD_LEN (int) ; 
 int V_CMD_GEN1 (int) ; 
 int /*<<< orphan*/  V_CMD_GEN2 (int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void recycle_fl_buf(struct freelQ *fl, int idx)
{
	struct freelQ_e *from = &fl->entries[idx];
	struct freelQ_e *to = &fl->entries[fl->pidx];

	fl->centries[fl->pidx] = fl->centries[idx];
	to->addr_lo = from->addr_lo;
	to->addr_hi = from->addr_hi;
	to->len_gen = G_CMD_LEN(from->len_gen) | V_CMD_GEN1(fl->genbit);
	wmb();
	to->gen2 = V_CMD_GEN2(fl->genbit);
	fl->credits++;

	if (++fl->pidx == fl->size) {
		fl->pidx = 0;
		fl->genbit ^= 1;
	}
}