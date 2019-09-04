#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct icn8505_data {TYPE_1__* client; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICN8505_REG_ADDR_WIDTH ; 
 int icn8505_write_xfer (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int icn8505_write_reg(struct icn8505_data *icn8505, int reg, u8 val)
{
	return icn8505_write_xfer(icn8505->client, icn8505->client->addr, reg,
				  ICN8505_REG_ADDR_WIDTH, &val, 1, false);
}