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
struct smu_table_context {TYPE_2__* power_play_table; } ;
struct smu_context {struct smu_table_context smu_table; } ;
struct TYPE_3__ {scalar_t__ format_revision; int /*<<< orphan*/  structuresize; } ;
struct TYPE_4__ {TYPE_1__ sHeader; } ;
typedef  TYPE_2__ ATOM_Vega20_POWERPLAYTABLE ;

/* Variables and functions */
 scalar_t__ ATOM_VEGA20_TABLE_REVISION_VEGA20 ; 
 int EINVAL ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int vega20_check_powerplay_table(struct smu_context *smu)
{
	ATOM_Vega20_POWERPLAYTABLE *powerplay_table = NULL;
	struct smu_table_context *table_context = &smu->smu_table;

	powerplay_table = table_context->power_play_table;

	if (powerplay_table->sHeader.format_revision < ATOM_VEGA20_TABLE_REVISION_VEGA20) {
		pr_err("Unsupported PPTable format!");
		return -EINVAL;
	}

	if (!powerplay_table->sHeader.structuresize) {
		pr_err("Invalid PowerPlay Table!");
		return -EINVAL;
	}

	return 0;
}