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
typedef  scalar_t__ u32 ;
struct rtl2832_dev {scalar_t__ post_bit_error; scalar_t__ post_bit_error_prev; } ;
struct dvb_frontend {struct rtl2832_dev* demodulator_priv; } ;

/* Variables and functions */

__attribute__((used)) static int rtl2832_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct rtl2832_dev *dev = fe->demodulator_priv;

	*ber = (dev->post_bit_error - dev->post_bit_error_prev);
	dev->post_bit_error_prev = dev->post_bit_error;

	return 0;
}