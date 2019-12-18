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
struct bq25890_device {int /*<<< orphan*/ * rmap_fields; } ;
typedef  enum bq25890_fields { ____Placeholder_bq25890_fields } bq25890_fields ;

/* Variables and functions */
 int regmap_field_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bq25890_field_write(struct bq25890_device *bq,
			       enum bq25890_fields field_id, u8 val)
{
	return regmap_field_write(bq->rmap_fields[field_id], val);
}