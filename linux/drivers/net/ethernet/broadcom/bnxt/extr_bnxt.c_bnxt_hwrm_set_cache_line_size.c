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
struct hwrm_func_cfg_input {int /*<<< orphan*/  options; int /*<<< orphan*/  enables; int /*<<< orphan*/  fid; int /*<<< orphan*/  member_0; } ;
struct bnxt {int hwrm_spec_code; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 int /*<<< orphan*/  FUNC_CFG_REQ_ENABLES_CACHE_LINESIZE ; 
 int /*<<< orphan*/  FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SIZE_128 ; 
 int /*<<< orphan*/  FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SIZE_64 ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_FUNC_CFG ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_func_cfg_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_func_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_set_cache_line_size(struct bnxt *bp, int size)
{
	struct hwrm_func_cfg_input req = {0};
	int rc;

	if (BNXT_VF(bp) || bp->hwrm_spec_code < 0x10803)
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_FUNC_CFG, -1, -1);
	req.fid = cpu_to_le16(0xffff);
	req.enables = cpu_to_le32(FUNC_CFG_REQ_ENABLES_CACHE_LINESIZE);
	req.options = FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SIZE_64;
	if (size == 128)
		req.options = FUNC_CFG_REQ_OPTIONS_CACHE_LINESIZE_SIZE_128;

	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	return rc;
}