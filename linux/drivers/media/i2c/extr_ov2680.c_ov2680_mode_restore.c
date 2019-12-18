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
struct ov2680_dev {int dummy; } ;

/* Variables and functions */
 int ov2680_load_regs (struct ov2680_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ov2680_mode_init_data ; 
 int ov2680_mode_set (struct ov2680_dev*) ; 

__attribute__((used)) static int ov2680_mode_restore(struct ov2680_dev *sensor)
{
	int ret;

	ret = ov2680_load_regs(sensor, &ov2680_mode_init_data);
	if (ret < 0)
		return ret;

	return ov2680_mode_set(sensor);
}