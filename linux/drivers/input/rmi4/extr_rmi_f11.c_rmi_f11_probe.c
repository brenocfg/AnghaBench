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
struct rmi_function {int /*<<< orphan*/  dev; } ;
struct f11_data {int /*<<< orphan*/  sensor; } ;

/* Variables and functions */
 struct f11_data* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int rmi_2d_sensor_configure_input (struct rmi_function*,int /*<<< orphan*/ *) ; 
 int rmi_f11_initialize (struct rmi_function*) ; 

__attribute__((used)) static int rmi_f11_probe(struct rmi_function *fn)
{
	int error;
	struct f11_data *f11;

	error = rmi_f11_initialize(fn);
	if (error)
		return error;

	f11 = dev_get_drvdata(&fn->dev);
	error = rmi_2d_sensor_configure_input(fn, &f11->sensor);
	if (error)
		return error;

	return 0;
}