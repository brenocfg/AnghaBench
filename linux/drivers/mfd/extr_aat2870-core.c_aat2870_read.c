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
struct aat2870_data {int /*<<< orphan*/  io_lock; } ;

/* Variables and functions */
 int __aat2870_read (struct aat2870_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aat2870_read(struct aat2870_data *aat2870, u8 addr, u8 *val)
{
	int ret;

	mutex_lock(&aat2870->io_lock);
	ret = __aat2870_read(aat2870, addr, val);
	mutex_unlock(&aat2870->io_lock);

	return ret;
}