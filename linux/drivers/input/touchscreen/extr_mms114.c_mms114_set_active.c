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
struct mms114_data {int dummy; } ;

/* Variables and functions */
 int MMS114_ACTIVE ; 
 int /*<<< orphan*/  MMS114_MODE_CONTROL ; 
 int MMS114_OPERATION_MODE_MASK ; 
 int mms114_read_reg (struct mms114_data*,int /*<<< orphan*/ ) ; 
 int mms114_write_reg (struct mms114_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mms114_set_active(struct mms114_data *data, bool active)
{
	int val;

	val = mms114_read_reg(data, MMS114_MODE_CONTROL);
	if (val < 0)
		return val;

	val &= ~MMS114_OPERATION_MODE_MASK;

	/* If active is false, sleep mode */
	if (active)
		val |= MMS114_ACTIVE;

	return mms114_write_reg(data, MMS114_MODE_CONTROL, val);
}