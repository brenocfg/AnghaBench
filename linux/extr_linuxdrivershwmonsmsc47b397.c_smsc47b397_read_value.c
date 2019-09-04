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
struct smsc47b397_data {int /*<<< orphan*/  lock; scalar_t__ addr; } ;

/* Variables and functions */
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int smsc47b397_read_value(struct smsc47b397_data *data, u8 reg)
{
	int res;

	mutex_lock(&data->lock);
	outb(reg, data->addr);
	res = inb_p(data->addr + 1);
	mutex_unlock(&data->lock);
	return res;
}