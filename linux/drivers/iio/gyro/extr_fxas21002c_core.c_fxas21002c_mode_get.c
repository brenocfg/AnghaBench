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
struct fxas21002c_data {int /*<<< orphan*/ * regmap_fields; } ;

/* Variables and functions */
 int FXAS21002C_MODE_ACTIVE ; 
 int FXAS21002C_MODE_READY ; 
 int FXAS21002C_MODE_STANDBY ; 
 size_t F_ACTIVE ; 
 size_t F_READY ; 
 int regmap_field_read (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static int fxas21002c_mode_get(struct fxas21002c_data *data)
{
	unsigned int active;
	unsigned int ready;
	int ret;

	ret = regmap_field_read(data->regmap_fields[F_ACTIVE], &active);
	if (ret < 0)
		return ret;
	if (active)
		return FXAS21002C_MODE_ACTIVE;

	ret = regmap_field_read(data->regmap_fields[F_READY], &ready);
	if (ret < 0)
		return ret;
	if (ready)
		return FXAS21002C_MODE_READY;

	return FXAS21002C_MODE_STANDBY;
}