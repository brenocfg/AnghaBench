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
struct t5403_data {int /*<<< orphan*/  lock; } ;
typedef  int s32 ;
typedef  int s16 ;

/* Variables and functions */
 scalar_t__ T5403_C_U16 (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int t5403_read (struct t5403_data*,int) ; 

__attribute__((used)) static int t5403_comp_temp(struct t5403_data *data, int *val)
{
	int ret;
	s16 t_r;

	mutex_lock(&data->lock);
	ret = t5403_read(data, false);
	if (ret < 0)
		goto done;
	t_r = ret;

	/* see EPCOS application note */
	*val = ((s32) T5403_C_U16(1) * t_r / 0x100 +
		(s32) T5403_C_U16(2) * 0x40) * 1000 / 0x10000;

done:
	mutex_unlock(&data->lock);
	return ret;
}