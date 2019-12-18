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
typedef  int /*<<< orphan*/  u16 ;
struct hwrm_dbg_coredump_initiate_input {void* segment_id; void* component_id; int /*<<< orphan*/  member_0; } ;
struct bnxt {int dummy; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_COREDUMP_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_DBG_COREDUMP_INITIATE ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_dbg_coredump_initiate_input*,int /*<<< orphan*/ ,int,int) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_dbg_coredump_initiate_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_dbg_coredump_initiate(struct bnxt *bp, u16 component_id,
					   u16 segment_id)
{
	struct hwrm_dbg_coredump_initiate_input req = {0};

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_DBG_COREDUMP_INITIATE, -1, -1);
	req.component_id = cpu_to_le16(component_id);
	req.segment_id = cpu_to_le16(segment_id);

	return hwrm_send_message(bp, &req, sizeof(req), HWRM_COREDUMP_TIMEOUT);
}