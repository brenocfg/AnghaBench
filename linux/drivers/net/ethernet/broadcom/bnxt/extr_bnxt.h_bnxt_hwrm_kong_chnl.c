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
struct input {scalar_t__ resp_addr; } ;
struct bnxt {int fw_cap; int /*<<< orphan*/  hwrm_cmd_kong_resp_dma_addr; } ;

/* Variables and functions */
 int BNXT_FW_CAP_KONG_MB_CHNL ; 
 scalar_t__ cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool bnxt_hwrm_kong_chnl(struct bnxt *bp, struct input *req)
{
	return (bp->fw_cap & BNXT_FW_CAP_KONG_MB_CHNL &&
		req->resp_addr == cpu_to_le64(bp->hwrm_cmd_kong_resp_dma_addr));
}