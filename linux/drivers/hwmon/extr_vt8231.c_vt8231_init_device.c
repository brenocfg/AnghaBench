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
struct vt8231_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VT8231_REG_TEMP1_CONFIG ; 
 int /*<<< orphan*/  VT8231_REG_TEMP2_CONFIG ; 
 int /*<<< orphan*/  vt8231_write_value (struct vt8231_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vt8231_init_device(struct vt8231_data *data)
{
	vt8231_write_value(data, VT8231_REG_TEMP1_CONFIG, 0);
	vt8231_write_value(data, VT8231_REG_TEMP2_CONFIG, 0);
}