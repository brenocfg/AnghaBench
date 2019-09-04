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
typedef  int /*<<< orphan*/  u16 ;
struct cec_adapter {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ IS_ERR_OR_NULL (struct cec_adapter*) ; 
 int /*<<< orphan*/  __cec_s_phys_addr (struct cec_adapter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void cec_s_phys_addr(struct cec_adapter *adap, u16 phys_addr, bool block)
{
	if (IS_ERR_OR_NULL(adap))
		return;

	mutex_lock(&adap->lock);
	__cec_s_phys_addr(adap, phys_addr, block);
	mutex_unlock(&adap->lock);
}