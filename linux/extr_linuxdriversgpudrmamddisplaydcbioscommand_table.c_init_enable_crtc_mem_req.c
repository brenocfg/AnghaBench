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
struct TYPE_2__ {int /*<<< orphan*/ * enable_crtc_mem_req; } ;
struct bios_parser {TYPE_1__ cmd_tbl; } ;

/* Variables and functions */
 int BIOS_CMD_TABLE_PARA_REVISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableCRTCMemReq ; 
 int /*<<< orphan*/ * enable_crtc_mem_req_v1 ; 

__attribute__((used)) static void init_enable_crtc_mem_req(struct bios_parser *bp)
{
	switch (BIOS_CMD_TABLE_PARA_REVISION(EnableCRTCMemReq)) {
	case 1:
		bp->cmd_tbl.enable_crtc_mem_req = enable_crtc_mem_req_v1;
		break;
	default:
		bp->cmd_tbl.enable_crtc_mem_req = NULL;
		break;
	}
}