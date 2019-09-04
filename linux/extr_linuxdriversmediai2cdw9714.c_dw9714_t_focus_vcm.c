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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;
struct dw9714_device {int /*<<< orphan*/  current_val; int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DW9714_DEFAULT_S ; 
 int /*<<< orphan*/  DW9714_VAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dw9714_i2c_write (struct i2c_client*,int /*<<< orphan*/ ) ; 
 struct i2c_client* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dw9714_t_focus_vcm(struct dw9714_device *dw9714_dev, u16 val)
{
	struct i2c_client *client = v4l2_get_subdevdata(&dw9714_dev->sd);

	dw9714_dev->current_val = val;

	return dw9714_i2c_write(client, DW9714_VAL(val, DW9714_DEFAULT_S));
}