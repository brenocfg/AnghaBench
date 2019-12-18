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
struct fintek_8250 {scalar_t__ base_port; } ;

/* Variables and functions */
 scalar_t__ ADDR_PORT ; 
 scalar_t__ DATA_PORT ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void sio_write_reg(struct fintek_8250 *pdata, u8 reg, u8 data)
{
	outb(reg, pdata->base_port + ADDR_PORT);
	outb(data, pdata->base_port + DATA_PORT);
}