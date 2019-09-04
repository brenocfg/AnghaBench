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
typedef  int /*<<< orphan*/  u32 ;
struct tda10071_dev {int /*<<< orphan*/  dvbv3_ber; } ;
struct dvb_frontend {struct tda10071_dev* demodulator_priv; } ;

/* Variables and functions */

__attribute__((used)) static int tda10071_read_ber(struct dvb_frontend *fe, u32 *ber)
{
	struct tda10071_dev *dev = fe->demodulator_priv;

	*ber = dev->dvbv3_ber;
	return 0;
}