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
typedef  int /*<<< orphan*/  u8 ;
struct stmpe {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __stmpe_reg_read (struct stmpe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int stmpe_reg_read(struct stmpe *stmpe, u8 reg)
{
	int ret;

	mutex_lock(&stmpe->lock);
	ret = __stmpe_reg_read(stmpe, reg);
	mutex_unlock(&stmpe->lock);

	return ret;
}