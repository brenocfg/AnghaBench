#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  code; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct s5k6aa_preset {int index; scalar_t__ clk_id; TYPE_1__ mbus_fmt; } ;
struct s5k6aa {struct s5k6aa_preset* presets; struct s5k6aa_preset* preset; int /*<<< orphan*/ * fiv; } ;
struct TYPE_4__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 size_t S5K6AA_INTERVAL_DEF_INDEX ; 
 int S5K6AA_MAX_PRESETS ; 
 int /*<<< orphan*/  S5K6AA_OUT_HEIGHT_DEF ; 
 int /*<<< orphan*/  S5K6AA_OUT_WIDTH_DEF ; 
 TYPE_2__* s5k6aa_formats ; 
 int /*<<< orphan*/ * s5k6aa_intervals ; 

__attribute__((used)) static void s5k6aa_presets_data_init(struct s5k6aa *s5k6aa)
{
	struct s5k6aa_preset *preset = &s5k6aa->presets[0];
	int i;

	for (i = 0; i < S5K6AA_MAX_PRESETS; i++) {
		preset->mbus_fmt.width	= S5K6AA_OUT_WIDTH_DEF;
		preset->mbus_fmt.height	= S5K6AA_OUT_HEIGHT_DEF;
		preset->mbus_fmt.code	= s5k6aa_formats[0].code;
		preset->index		= i;
		preset->clk_id		= 0;
		preset++;
	}

	s5k6aa->fiv = &s5k6aa_intervals[S5K6AA_INTERVAL_DEF_INDEX];
	s5k6aa->preset = &s5k6aa->presets[0];
}