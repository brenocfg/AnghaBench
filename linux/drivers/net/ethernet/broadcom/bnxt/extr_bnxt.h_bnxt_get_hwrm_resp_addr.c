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
struct input {int dummy; } ;
struct bnxt {void* hwrm_cmd_kong_resp_addr; void* hwrm_cmd_resp_addr; } ;

/* Variables and functions */
 scalar_t__ bnxt_hwrm_kong_chnl (struct bnxt*,struct input*) ; 

__attribute__((used)) static inline void *bnxt_get_hwrm_resp_addr(struct bnxt *bp, void *req)
{
	if (bnxt_hwrm_kong_chnl(bp, (struct input *)req))
		return bp->hwrm_cmd_kong_resp_addr;
	else
		return bp->hwrm_cmd_resp_addr;
}