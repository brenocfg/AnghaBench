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
typedef  int u16 ;
struct w83627ehf_data {int /*<<< orphan*/  lock; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ ADDR_REG_OFFSET ; 
 scalar_t__ DATA_REG_OFFSET ; 
 int is_word_sized (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  w83627ehf_set_bank (struct w83627ehf_data*,int) ; 

__attribute__((used)) static int w83627ehf_write_value(struct w83627ehf_data *data, u16 reg,
				 u16 value)
{
	int word_sized = is_word_sized(reg);

	mutex_lock(&data->lock);

	w83627ehf_set_bank(data, reg);
	outb_p(reg & 0xff, data->addr + ADDR_REG_OFFSET);
	if (word_sized) {
		outb_p(value >> 8, data->addr + DATA_REG_OFFSET);
		outb_p((reg & 0xff) + 1,
		       data->addr + ADDR_REG_OFFSET);
	}
	outb_p(value & 0xff, data->addr + DATA_REG_OFFSET);

	mutex_unlock(&data->lock);
	return 0;
}