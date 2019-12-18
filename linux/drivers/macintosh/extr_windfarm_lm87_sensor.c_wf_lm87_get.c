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
struct wf_sensor {struct wf_lm87_sensor* priv; } ;
struct wf_lm87_sensor {int /*<<< orphan*/ * i2c; } ;
typedef  int s32 ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  LM87_INT_TEMP ; 
 int wf_lm87_read_reg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wf_lm87_get(struct wf_sensor *sr, s32 *value)
{
	struct wf_lm87_sensor *lm = sr->priv;
	s32 temp;

	if (lm->i2c == NULL)
		return -ENODEV;

#define LM87_INT_TEMP		0x27

	/* Read temperature register */
	temp = wf_lm87_read_reg(lm->i2c, LM87_INT_TEMP);
	if (temp < 0)
		return temp;
	*value = temp << 16;

	return 0;
}