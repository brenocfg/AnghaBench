#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int r_offset; int r_length; } ;
struct msb_data {int addr_valid; TYPE_2__ reg_addr; TYPE_1__* card; } ;
struct memstick_request {int dummy; } ;
struct TYPE_3__ {struct memstick_request current_mrq; } ;

/* Variables and functions */
 int /*<<< orphan*/  MS_TPC_READ_REG ; 
 int /*<<< orphan*/  MS_TPC_SET_RW_REG_ADRS ; 
 int /*<<< orphan*/  memstick_init_req (struct memstick_request*,int /*<<< orphan*/ ,TYPE_2__*,int) ; 

__attribute__((used)) static int msb_read_regs(struct msb_data *msb, int offset, int len)
{
	struct memstick_request *req = &msb->card->current_mrq;

	if (msb->reg_addr.r_offset != offset ||
	    msb->reg_addr.r_length != len || !msb->addr_valid) {

		msb->reg_addr.r_offset = offset;
		msb->reg_addr.r_length = len;
		msb->addr_valid = true;

		memstick_init_req(req, MS_TPC_SET_RW_REG_ADRS,
			&msb->reg_addr, sizeof(msb->reg_addr));
		return 0;
	}

	memstick_init_req(req, MS_TPC_READ_REG, NULL, len);
	return 1;
}