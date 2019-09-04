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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int lm90_read_reg (struct i2c_client*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lm90_read16(struct i2c_client *client, u8 regh, u8 regl)
{
	int oldh, newh, l;

	/*
	 * There is a trick here. We have to read two registers to have the
	 * sensor temperature, but we have to beware a conversion could occur
	 * between the readings. The datasheet says we should either use
	 * the one-shot conversion register, which we don't want to do
	 * (disables hardware monitoring) or monitor the busy bit, which is
	 * impossible (we can't read the values and monitor that bit at the
	 * exact same time). So the solution used here is to read the high
	 * byte once, then the low byte, then the high byte again. If the new
	 * high byte matches the old one, then we have a valid reading. Else
	 * we have to read the low byte again, and now we believe we have a
	 * correct reading.
	 */
	oldh = lm90_read_reg(client, regh);
	if (oldh < 0)
		return oldh;
	l = lm90_read_reg(client, regl);
	if (l < 0)
		return l;
	newh = lm90_read_reg(client, regh);
	if (newh < 0)
		return newh;
	if (oldh != newh) {
		l = lm90_read_reg(client, regl);
		if (l < 0)
			return l;
	}
	return (newh << 8) | l;
}