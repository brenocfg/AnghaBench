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
struct TYPE_2__ {int /*<<< orphan*/  get_smu_clock_info; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_smu_clock_info_v3_1 ; 

__attribute__((used)) static void init_get_smu_clock_info(struct bios_parser *bp)
{
	/* TODO add switch for table vrsion */
	bp->cmd_tbl.get_smu_clock_info = get_smu_clock_info_v3_1;

}