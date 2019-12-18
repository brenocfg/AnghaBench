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
struct w83627hf_data {int /*<<< orphan*/  lock; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ W83781D_ADDR_REG_OFFSET ; 
 scalar_t__ W83781D_DATA_REG_OFFSET ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 
 int /*<<< orphan*/  w83627hf_reset_bank (struct w83627hf_data*,int) ; 
 int /*<<< orphan*/  w83627hf_set_bank (struct w83627hf_data*,int) ; 

__attribute__((used)) static int w83627hf_read_value(struct w83627hf_data *data, u16 reg)
{
	int res, word_sized;

	mutex_lock(&data->lock);
	word_sized = (((reg & 0xff00) == 0x100)
		   || ((reg & 0xff00) == 0x200))
		  && (((reg & 0x00ff) == 0x50)
		   || ((reg & 0x00ff) == 0x53)
		   || ((reg & 0x00ff) == 0x55));
	w83627hf_set_bank(data, reg);
	outb_p(reg & 0xff, data->addr + W83781D_ADDR_REG_OFFSET);
	res = inb_p(data->addr + W83781D_DATA_REG_OFFSET);
	if (word_sized) {
		outb_p((reg & 0xff) + 1,
		       data->addr + W83781D_ADDR_REG_OFFSET);
		res =
		    (res << 8) + inb_p(data->addr +
				       W83781D_DATA_REG_OFFSET);
	}
	w83627hf_reset_bank(data, reg);
	mutex_unlock(&data->lock);
	return res;
}