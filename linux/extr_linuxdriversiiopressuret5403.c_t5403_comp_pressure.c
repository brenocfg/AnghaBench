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
typedef  int u16 ;
struct t5403_data {int /*<<< orphan*/  lock; } ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 int T5403_C (int) ; 
 int T5403_C_U16 (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int t5403_read (struct t5403_data*,int) ; 

__attribute__((used)) static int t5403_comp_pressure(struct t5403_data *data, int *val, int *val2)
{
	int ret;
	s16 t_r;
	u16 p_r;
	s32 S, O, X;

	mutex_lock(&data->lock);

	ret = t5403_read(data, false);
	if (ret < 0)
		goto done;
	t_r = ret;

	ret = t5403_read(data, true);
	if (ret < 0)
		goto done;
	p_r = ret;

	/* see EPCOS application note */
	S = T5403_C_U16(3) + (s32) T5403_C_U16(4) * t_r / 0x20000 +
		T5403_C(5) * t_r / 0x8000 * t_r / 0x80000 +
		T5403_C(9) * t_r / 0x8000 * t_r / 0x8000 * t_r / 0x10000;

	O = T5403_C(6) * 0x4000 + T5403_C(7) * t_r / 8 +
		T5403_C(8) * t_r / 0x8000 * t_r / 16 +
		T5403_C(9) * t_r / 0x8000 * t_r / 0x10000 * t_r;

	X = (S * p_r + O) / 0x4000;

	X += ((X - 75000) * (X - 75000) / 0x10000 - 9537) *
	    T5403_C(10) / 0x10000;

	*val = X / 1000;
	*val2 = (X % 1000) * 1000;

done:
	mutex_unlock(&data->lock);
	return ret;
}