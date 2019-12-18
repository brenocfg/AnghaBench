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
struct icn8505_data {int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ICN8505_PROG_I2C_ADDR ; 
 int /*<<< orphan*/  ICN8505_PROG_REG_ADDR_WIDTH ; 
 int icn8505_read_xfer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,void*,int,int) ; 

__attribute__((used)) static int icn8505_read_prog_data(struct icn8505_data *icn8505, int reg,
				  void *buf, int len)
{
	return icn8505_read_xfer(icn8505->client, ICN8505_PROG_I2C_ADDR, reg,
				 ICN8505_PROG_REG_ADDR_WIDTH, buf, len, false);
}