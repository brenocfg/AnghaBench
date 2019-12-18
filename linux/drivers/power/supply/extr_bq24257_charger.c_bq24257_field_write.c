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
struct bq24257_device {int /*<<< orphan*/ * rmap_fields; } ;
typedef  enum bq24257_fields { ____Placeholder_bq24257_fields } bq24257_fields ;

/* Variables and functions */
 int regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq24257_field_write(struct bq24257_device *bq,
			       enum bq24257_fields field_id, u8 val)
{
	return regmap_field_write(bq->rmap_fields[field_id], val);
}