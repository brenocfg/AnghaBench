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
struct rt9455_info {int /*<<< orphan*/ * regmap_fields; } ;
typedef  enum rt9455_fields { ____Placeholder_rt9455_fields } rt9455_fields ;

/* Variables and functions */
 int regmap_field_write (int /*<<< orphan*/ ,unsigned int) ; 
 unsigned int rt9455_find_idx (int const*,int,int) ; 

__attribute__((used)) static int rt9455_set_field_val(struct rt9455_info *info,
				enum rt9455_fields field,
				const int tbl[], int tbl_size, int val)
{
	unsigned int idx = rt9455_find_idx(tbl, tbl_size, val);

	return regmap_field_write(info->regmap_fields[field], idx);
}