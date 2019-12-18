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
struct i2c_msg {int len; int /*<<< orphan*/ * buf; } ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  mb862xx_i2c_read_byte (struct i2c_adapter*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mb862xx_i2c_read(struct i2c_adapter *adap, struct i2c_msg *m)
{
	int i, ret = 0;
	int last = m->len - 1;

	for (i = 0; i < m->len; i++) {
		if (!mb862xx_i2c_read_byte(adap, &m->buf[i], i == last)) {
			ret = -EIO;
			break;
		}
	}
	return ret;
}