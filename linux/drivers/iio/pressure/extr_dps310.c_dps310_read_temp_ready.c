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
typedef  int /*<<< orphan*/  val ;
typedef  int u8 ;
struct dps310_data {int /*<<< orphan*/  temp_raw; int /*<<< orphan*/  regmap; } ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/  DPS310_TMP_BASE ; 
 int regmap_bulk_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sign_extend32 (int,int) ; 

__attribute__((used)) static int dps310_read_temp_ready(struct dps310_data *data)
{
	int rc;
	u8 val[3];
	s32 raw;

	rc = regmap_bulk_read(data->regmap, DPS310_TMP_BASE, val, sizeof(val));
	if (rc < 0)
		return rc;

	raw = (val[0] << 16) | (val[1] << 8) | val[2];
	data->temp_raw = sign_extend32(raw, 23);

	return 0;
}