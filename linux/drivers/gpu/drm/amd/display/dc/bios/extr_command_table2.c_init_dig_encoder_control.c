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
typedef  int uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/ * dig_encoder_control; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  digxencodercontrol ; 
 int /*<<< orphan*/  dm_output_to_console (char*,int) ; 
 int /*<<< orphan*/ * encoder_control_digx_v1_5 ; 

__attribute__((used)) static void init_dig_encoder_control(struct bios_parser *bp)
{
	uint32_t version =
		BIOS_CMD_TABLE_PARA_REVISION(digxencodercontrol);

	switch (version) {
	case 5:
		bp->cmd_tbl.dig_encoder_control = encoder_control_digx_v1_5;
		break;
	default:
		dm_output_to_console("Don't have dig_encoder_control for v%d\n", version);
		bp->cmd_tbl.dig_encoder_control = NULL;
		break;
	}
}