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
struct nct6775_data {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ ADDR_REG_OFFSET ; 
 scalar_t__ DATA_REG_OFFSET ; 
 int inb_p (scalar_t__) ; 
 int is_word_sized (struct nct6775_data*,int) ; 
 int /*<<< orphan*/  nct6775_set_bank (struct nct6775_data*,int) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static u16 nct6775_read_value(struct nct6775_data *data, u16 reg)
{
	int res, word_sized = is_word_sized(data, reg);

	nct6775_set_bank(data, reg);
	outb_p(reg & 0xff, data->addr + ADDR_REG_OFFSET);
	res = inb_p(data->addr + DATA_REG_OFFSET);
	if (word_sized) {
		outb_p((reg & 0xff) + 1,
		       data->addr + ADDR_REG_OFFSET);
		res = (res << 8) + inb_p(data->addr + DATA_REG_OFFSET);
	}
	return res;
}