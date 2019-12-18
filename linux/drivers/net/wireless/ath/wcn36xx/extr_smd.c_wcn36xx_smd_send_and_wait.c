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
struct wcn36xx_hal_msg_header {int /*<<< orphan*/  msg_type; } ;
struct wcn36xx {int /*<<< orphan*/  hal_rsp_compl; scalar_t__ hal_buf; int /*<<< orphan*/  smd_channel; } ;

/* Variables and functions */
 int ETIME ; 
 int /*<<< orphan*/  HAL_MSG_TIMEOUT ; 
 int /*<<< orphan*/  WCN36XX_DBG_SMD ; 
 int /*<<< orphan*/  WCN36XX_DBG_SMD_DUMP ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  jiffies_to_msecs (unsigned long) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int rpmsg_send (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 scalar_t__ wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wcn36xx_dbg_dump (int /*<<< orphan*/ ,char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  wcn36xx_err (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int wcn36xx_smd_send_and_wait(struct wcn36xx *wcn, size_t len)
{
	int ret;
	unsigned long start;
	struct wcn36xx_hal_msg_header *hdr =
		(struct wcn36xx_hal_msg_header *)wcn->hal_buf;
	u16 req_type = hdr->msg_type;

	wcn36xx_dbg_dump(WCN36XX_DBG_SMD_DUMP, "HAL >>> ", wcn->hal_buf, len);

	init_completion(&wcn->hal_rsp_compl);
	start = jiffies;
	ret = rpmsg_send(wcn->smd_channel, wcn->hal_buf, len);
	if (ret) {
		wcn36xx_err("HAL TX failed for req %d\n", req_type);
		goto out;
	}
	if (wait_for_completion_timeout(&wcn->hal_rsp_compl,
		msecs_to_jiffies(HAL_MSG_TIMEOUT)) <= 0) {
		wcn36xx_err("Timeout! No SMD response to req %d in %dms\n",
			    req_type, HAL_MSG_TIMEOUT);
		ret = -ETIME;
		goto out;
	}
	wcn36xx_dbg(WCN36XX_DBG_SMD,
		    "SMD command (req %d, rsp %d) completed in %dms\n",
		    req_type, hdr->msg_type,
		    jiffies_to_msecs(jiffies - start));
out:
	return ret;
}