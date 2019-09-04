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
struct stmpe {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int __stmpe_enable (struct stmpe*,unsigned int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int stmpe_enable(struct stmpe *stmpe, unsigned int blocks)
{
	int ret;

	mutex_lock(&stmpe->lock);
	ret = __stmpe_enable(stmpe, blocks);
	mutex_unlock(&stmpe->lock);

	return ret;
}