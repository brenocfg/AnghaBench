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
struct input {int /*<<< orphan*/  req_type; } ;
struct bnxt {int fw_cap; } ;

/* Variables and functions */
 int BNXT_FW_CAP_KONG_MB_CHNL ; 
 scalar_t__ bnxt_cfa_hwrm_message (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool bnxt_kong_hwrm_message(struct bnxt *bp, struct input *req)
{
	return (bp->fw_cap & BNXT_FW_CAP_KONG_MB_CHNL &&
		bnxt_cfa_hwrm_message(le16_to_cpu(req->req_type)));
}