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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int t3_wait_op_done_val (struct adapter*,int,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int t3_wait_op_done(struct adapter *adapter, int reg, u32 mask,
				  int polarity, int attempts, int delay)
{
	return t3_wait_op_done_val(adapter, reg, mask, polarity, attempts,
				   delay, NULL);
}