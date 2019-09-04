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
typedef  int u32 ;
struct pxa_i2c {int req_slave_addr; int /*<<< orphan*/  msg; } ;

/* Variables and functions */
 int ICR_ALDIE ; 
 int ICR_START ; 
 int ICR_STOP ; 
 int ICR_TB ; 
 int /*<<< orphan*/  _ICR (struct pxa_i2c*) ; 
 int /*<<< orphan*/  _IDBR (struct pxa_i2c*) ; 
 int i2c_pxa_addr_byte (int /*<<< orphan*/ ) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void i2c_pxa_start_message(struct pxa_i2c *i2c)
{
	u32 icr;

	/*
	 * Step 1: target slave address into IDBR
	 */
	writel(i2c_pxa_addr_byte(i2c->msg), _IDBR(i2c));
	i2c->req_slave_addr = i2c_pxa_addr_byte(i2c->msg);

	/*
	 * Step 2: initiate the write.
	 */
	icr = readl(_ICR(i2c)) & ~(ICR_STOP | ICR_ALDIE);
	writel(icr | ICR_START | ICR_TB, _ICR(i2c));
}