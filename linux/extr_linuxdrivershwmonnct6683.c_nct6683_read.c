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
struct nct6683_data {scalar_t__ addr; } ;

/* Variables and functions */
 scalar_t__ EC_DATA_REG ; 
 scalar_t__ EC_INDEX_REG ; 
 scalar_t__ EC_PAGE_REG ; 
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  outb_p (int,scalar_t__) ; 

__attribute__((used)) static u16 nct6683_read(struct nct6683_data *data, u16 reg)
{
	int res;

	outb_p(0xff, data->addr + EC_PAGE_REG);		/* unlock */
	outb_p(reg >> 8, data->addr + EC_PAGE_REG);
	outb_p(reg & 0xff, data->addr + EC_INDEX_REG);
	res = inb_p(data->addr + EC_DATA_REG);
	return res;
}