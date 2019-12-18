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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  t_wdata ;
struct lg4ff_wheel_data {char const* real_tag; char const* real_name; int /*<<< orphan*/  alternate_modes; int /*<<< orphan*/  set_range; int /*<<< orphan*/  max_range; int /*<<< orphan*/  min_range; int /*<<< orphan*/  combine; int /*<<< orphan*/  const real_product_id; int /*<<< orphan*/  product_id; } ;
struct lg4ff_wheel {int /*<<< orphan*/  set_range; int /*<<< orphan*/  max_range; int /*<<< orphan*/  min_range; int /*<<< orphan*/  product_id; } ;
struct lg4ff_multimode_wheel {char* real_tag; char* real_name; int /*<<< orphan*/  alternate_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (struct lg4ff_wheel_data* const,struct lg4ff_wheel_data*,int) ; 

__attribute__((used)) static void lg4ff_init_wheel_data(struct lg4ff_wheel_data * const wdata, const struct lg4ff_wheel *wheel,
				  const struct lg4ff_multimode_wheel *mmode_wheel,
				  const u16 real_product_id)
{
	u32 alternate_modes = 0;
	const char *real_tag = NULL;
	const char *real_name = NULL;

	if (mmode_wheel) {
		alternate_modes = mmode_wheel->alternate_modes;
		real_tag = mmode_wheel->real_tag;
		real_name = mmode_wheel->real_name;
	}

	{
		struct lg4ff_wheel_data t_wdata =  { .product_id = wheel->product_id,
						     .real_product_id = real_product_id,
						     .combine = 0,
						     .min_range = wheel->min_range,
						     .max_range = wheel->max_range,
						     .set_range = wheel->set_range,
						     .alternate_modes = alternate_modes,
						     .real_tag = real_tag,
						     .real_name = real_name };

		memcpy(wdata, &t_wdata, sizeof(t_wdata));
	}
}