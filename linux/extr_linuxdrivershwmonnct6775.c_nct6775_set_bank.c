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
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct nct6775_data {scalar_t__ bank; scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ ADDR_REG_OFFSET ; 
 scalar_t__ DATA_REG_OFFSET ; 
 scalar_t__ NCT6775_REG_BANK ; 
 int /*<<< orphan*/  outb_p (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void nct6775_set_bank(struct nct6775_data *data, u16 reg)
{
	u8 bank = reg >> 8;

	if (data->bank != bank) {
		outb_p(NCT6775_REG_BANK, data->addr + ADDR_REG_OFFSET);
		outb_p(bank, data->addr + DATA_REG_OFFSET);
		data->bank = bank;
	}
}