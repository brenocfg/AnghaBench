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
struct wf_fcu_priv {int dummy; } ;
struct wf_fcu_fan {int min; int max; int target; int id; struct wf_fcu_priv* fcu_priv; } ;
struct wf_control {struct wf_fcu_fan* priv; } ;
typedef  int s32 ;

/* Variables and functions */
 int EIO ; 
 int wf_fcu_write_reg (struct wf_fcu_priv*,int,unsigned char*,int) ; 

__attribute__((used)) static int wf_fcu_fan_set_pwm(struct wf_control *ct, s32 value)
{
	struct wf_fcu_fan *fan = ct->priv;
	struct wf_fcu_priv *pv = fan->fcu_priv;
	unsigned char buf[2];
	int rc;

	if (value < fan->min)
		value = fan->min;
	if (value > fan->max)
		value = fan->max;

	fan->target = value;

	value = (value * 2559) / 1000;
	buf[0] = value;
	rc = wf_fcu_write_reg(pv, 0x30 + (fan->id * 2), buf, 1);
	if (rc < 0)
		return -EIO;
	return 0;
}