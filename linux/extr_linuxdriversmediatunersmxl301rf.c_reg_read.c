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
typedef  int /*<<< orphan*/  wbuf ;
typedef  int u8 ;
struct mxl301rf_state {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_recv (int /*<<< orphan*/ ,int*,int) ; 
 int raw_write (struct mxl301rf_state*,int*,int) ; 

__attribute__((used)) static int reg_read(struct mxl301rf_state *state, u8 reg, u8 *val)
{
	u8 wbuf[2] = { 0xfb, reg };
	int ret;

	ret = raw_write(state, wbuf, sizeof(wbuf));
	if (ret == 0)
		ret = i2c_master_recv(state->i2c, val, 1);
	if (ret >= 0 && ret < 1)
		ret = -EIO;
	return (ret == 1) ? 0 : ret;
}