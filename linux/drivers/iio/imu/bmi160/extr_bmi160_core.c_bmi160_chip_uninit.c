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
struct bmi160_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMI160_ACCEL ; 
 int /*<<< orphan*/  BMI160_GYRO ; 
 int /*<<< orphan*/  bmi160_set_mode (struct bmi160_data*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bmi160_chip_uninit(void *data)
{
	struct bmi160_data *bmi_data = data;

	bmi160_set_mode(bmi_data, BMI160_GYRO, false);
	bmi160_set_mode(bmi_data, BMI160_ACCEL, false);
}