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
struct rtl2832_dev {int /*<<< orphan*/  i2c_gate_work; } ;
struct i2c_mux_core {int dummy; } ;

/* Variables and functions */
 struct rtl2832_dev* i2c_mux_priv (struct i2c_mux_core*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int) ; 

__attribute__((used)) static int rtl2832_deselect(struct i2c_mux_core *muxc, u32 chan_id)
{
	struct rtl2832_dev *dev = i2c_mux_priv(muxc);

	schedule_delayed_work(&dev->i2c_gate_work, usecs_to_jiffies(100));
	return 0;
}