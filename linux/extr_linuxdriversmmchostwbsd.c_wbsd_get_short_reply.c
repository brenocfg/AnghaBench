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
struct wbsd_host {int dummy; } ;
struct mmc_command {int* resp; int /*<<< orphan*/  error; } ;

/* Variables and functions */
 int /*<<< orphan*/  EILSEQ ; 
 int /*<<< orphan*/  WBSD_IDX_RESP12 ; 
 int /*<<< orphan*/  WBSD_IDX_RESP13 ; 
 int /*<<< orphan*/  WBSD_IDX_RESP14 ; 
 int /*<<< orphan*/  WBSD_IDX_RESP15 ; 
 int /*<<< orphan*/  WBSD_IDX_RESP16 ; 
 int /*<<< orphan*/  WBSD_IDX_RSPLEN ; 
 int WBSD_RSP_SHORT ; 
 int wbsd_read_index (struct wbsd_host*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wbsd_get_short_reply(struct wbsd_host *host,
					struct mmc_command *cmd)
{
	/*
	 * Correct response type?
	 */
	if (wbsd_read_index(host, WBSD_IDX_RSPLEN) != WBSD_RSP_SHORT) {
		cmd->error = -EILSEQ;
		return;
	}

	cmd->resp[0]  = wbsd_read_index(host, WBSD_IDX_RESP12) << 24;
	cmd->resp[0] |= wbsd_read_index(host, WBSD_IDX_RESP13) << 16;
	cmd->resp[0] |= wbsd_read_index(host, WBSD_IDX_RESP14) << 8;
	cmd->resp[0] |= wbsd_read_index(host, WBSD_IDX_RESP15) << 0;
	cmd->resp[1]  = wbsd_read_index(host, WBSD_IDX_RESP16) << 24;
}