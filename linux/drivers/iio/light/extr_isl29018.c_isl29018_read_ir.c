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
struct isl29018_chip {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISL29018_CMD1_OPMODE_IR_ONCE ; 
 int isl29018_read_sensor_input (struct isl29018_chip*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isl29018_read_ir(struct isl29018_chip *chip, int *ir)
{
	int ir_data;

	ir_data = isl29018_read_sensor_input(chip,
					     ISL29018_CMD1_OPMODE_IR_ONCE);
	if (ir_data < 0)
		return ir_data;

	*ir = ir_data;

	return 0;
}