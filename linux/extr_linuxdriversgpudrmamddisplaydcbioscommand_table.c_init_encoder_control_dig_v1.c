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
struct cmd_tbl {int /*<<< orphan*/  dig_encoder_control; int /*<<< orphan*/ * encoder_control_dig2; int /*<<< orphan*/ * encoder_control_dig1; } ;
struct bios_parser {struct cmd_tbl cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DIG1EncoderControl ; 
 int /*<<< orphan*/  DIG2EncoderControl ; 
 int /*<<< orphan*/ * encoder_control_dig1_v1 ; 
 int /*<<< orphan*/ * encoder_control_dig2_v1 ; 
 int /*<<< orphan*/  encoder_control_dig_v1 ; 

__attribute__((used)) static void init_encoder_control_dig_v1(struct bios_parser *bp)
{
	struct cmd_tbl *cmd_tbl = &bp->cmd_tbl;

	if (1 == BIOS_CMD_TABLE_PARA_REVISION(DIG1EncoderControl))
		cmd_tbl->encoder_control_dig1 = encoder_control_dig1_v1;
	else
		cmd_tbl->encoder_control_dig1 = NULL;

	if (1 == BIOS_CMD_TABLE_PARA_REVISION(DIG2EncoderControl))
		cmd_tbl->encoder_control_dig2 = encoder_control_dig2_v1;
	else
		cmd_tbl->encoder_control_dig2 = NULL;

	cmd_tbl->dig_encoder_control = encoder_control_dig_v1;
}