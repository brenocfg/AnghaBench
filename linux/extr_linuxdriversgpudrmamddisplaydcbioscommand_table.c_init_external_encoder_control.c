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
struct TYPE_2__ {int /*<<< orphan*/ * external_encoder_control; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExternalEncoderControl ; 
 int /*<<< orphan*/ * external_encoder_control_v3 ; 

__attribute__((used)) static void init_external_encoder_control(
	struct bios_parser *bp)
{
	switch (BIOS_CMD_TABLE_PARA_REVISION(ExternalEncoderControl)) {
	case 3:
		bp->cmd_tbl.external_encoder_control =
				external_encoder_control_v3;
		break;
	default:
		bp->cmd_tbl.external_encoder_control = NULL;
		break;
	}
}