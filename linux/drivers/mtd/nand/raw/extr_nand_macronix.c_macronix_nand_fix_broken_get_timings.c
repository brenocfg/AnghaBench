#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  set_feature_list; int /*<<< orphan*/  get_feature_list; int /*<<< orphan*/  model; int /*<<< orphan*/  supports_set_get_features; } ;
struct nand_chip {TYPE_1__ parameters; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char const* const*) ; 
 int /*<<< orphan*/  ONFI_FEATURE_ADDR_TIMING_MODE ; 
 int /*<<< orphan*/  bitmap_clear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strcmp (char const* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void macronix_nand_fix_broken_get_timings(struct nand_chip *chip)
{
	unsigned int i;
	static const char * const broken_get_timings[] = {
		"MX30LF1G18AC",
		"MX30LF1G28AC",
		"MX30LF2G18AC",
		"MX30LF2G28AC",
		"MX30LF4G18AC",
		"MX30LF4G28AC",
		"MX60LF8G18AC",
		"MX30UF1G18AC",
		"MX30UF1G16AC",
		"MX30UF2G18AC",
		"MX30UF2G16AC",
		"MX30UF4G18AC",
		"MX30UF4G16AC",
		"MX30UF4G28AC",
	};

	if (!chip->parameters.supports_set_get_features)
		return;

	for (i = 0; i < ARRAY_SIZE(broken_get_timings); i++) {
		if (!strcmp(broken_get_timings[i], chip->parameters.model))
			break;
	}

	if (i == ARRAY_SIZE(broken_get_timings))
		return;

	bitmap_clear(chip->parameters.get_feature_list,
		     ONFI_FEATURE_ADDR_TIMING_MODE, 1);
	bitmap_clear(chip->parameters.set_feature_list,
		     ONFI_FEATURE_ADDR_TIMING_MODE, 1);
}