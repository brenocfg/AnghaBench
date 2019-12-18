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
typedef  int /*<<< orphan*/  u8 ;
struct qm1d1c0042_state {int /*<<< orphan*/  i2c; } ;

/* Variables and functions */
 int EIO ; 
 int i2c_master_send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int reg_write(struct qm1d1c0042_state *state, u8 reg, u8 val)
{
	u8 wbuf[2] = { reg, val };
	int ret;

	ret = i2c_master_send(state->i2c, wbuf, sizeof(wbuf));
	if (ret >= 0 && ret < sizeof(wbuf))
		ret = -EIO;
	return (ret == sizeof(wbuf)) ? 0 : ret;
}