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
struct isl6421 {int /*<<< orphan*/  i2c; int /*<<< orphan*/  override_and; int /*<<< orphan*/  config; int /*<<< orphan*/  override_or; int /*<<< orphan*/  i2c_addr; } ;
struct i2c_msg {int len; int /*<<< orphan*/ * buf; int /*<<< orphan*/  flags; int /*<<< orphan*/  addr; } ;
struct dvb_frontend {scalar_t__ sec_priv; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  ISL6421_LLC1 ; 
 int i2c_transfer (int /*<<< orphan*/ ,struct i2c_msg*,int) ; 

__attribute__((used)) static int isl6421_enable_high_lnb_voltage(struct dvb_frontend *fe, long arg)
{
	struct isl6421 *isl6421 = (struct isl6421 *) fe->sec_priv;
	struct i2c_msg msg = {	.addr = isl6421->i2c_addr, .flags = 0,
				.buf = &isl6421->config,
				.len = sizeof(isl6421->config) };

	if (arg)
		isl6421->config |= ISL6421_LLC1;
	else
		isl6421->config &= ~ISL6421_LLC1;

	isl6421->config |= isl6421->override_or;
	isl6421->config &= isl6421->override_and;

	return (i2c_transfer(isl6421->i2c, &msg, 1) == 1) ? 0 : -EIO;
}