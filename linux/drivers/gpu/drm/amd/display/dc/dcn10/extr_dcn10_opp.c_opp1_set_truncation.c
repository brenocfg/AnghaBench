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
struct dcn10_opp {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  TRUNCATE_MODE; int /*<<< orphan*/  TRUNCATE_DEPTH; int /*<<< orphan*/  TRUNCATE_ENABLED; } ;
struct bit_depth_reduction_params {TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  FMT_BIT_DEPTH_CONTROL ; 
 int /*<<< orphan*/  FMT_TRUNCATE_DEPTH ; 
 int /*<<< orphan*/  FMT_TRUNCATE_EN ; 
 int /*<<< orphan*/  FMT_TRUNCATE_MODE ; 
 int /*<<< orphan*/  REG_UPDATE_3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void opp1_set_truncation(
		struct dcn10_opp *oppn10,
		const struct bit_depth_reduction_params *params)
{
	REG_UPDATE_3(FMT_BIT_DEPTH_CONTROL,
		FMT_TRUNCATE_EN, params->flags.TRUNCATE_ENABLED,
		FMT_TRUNCATE_DEPTH, params->flags.TRUNCATE_DEPTH,
		FMT_TRUNCATE_MODE, params->flags.TRUNCATE_MODE);
}