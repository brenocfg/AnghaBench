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
typedef  int /*<<< orphan*/  u8 ;
struct si1133_data {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int si1133_force_measurement (struct si1133_data*) ; 

__attribute__((used)) static int si1133_bulk_read(struct si1133_data *data, u8 start_reg, u8 length,
			    u8 *buffer)
{
	int err;

	err = si1133_force_measurement(data);
	if (err)
		return err;

	return regmap_bulk_read(data->regmap, start_reg, buffer, length);
}