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
struct hubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST ; 
 int /*<<< orphan*/  REG_UPDATE_SEQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void hubbub1_wm_change_req_wa(struct hubbub *hubbub)
{
	REG_UPDATE_SEQ(DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, 0, 1);
}