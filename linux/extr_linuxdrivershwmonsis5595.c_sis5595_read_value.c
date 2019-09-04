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
struct sis5595_data {int /*<<< orphan*/  lock; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ SIS5595_ADDR_REG_OFFSET ; 
 scalar_t__ SIS5595_DATA_REG_OFFSET ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int sis5595_read_value(struct sis5595_data *data, u8 reg)
{
	int res;

	mutex_lock(&data->lock);
	outb_p(reg, data->addr + SIS5595_ADDR_REG_OFFSET);
	res = inb_p(data->addr + SIS5595_DATA_REG_OFFSET);
	mutex_unlock(&data->lock);
	return res;
}