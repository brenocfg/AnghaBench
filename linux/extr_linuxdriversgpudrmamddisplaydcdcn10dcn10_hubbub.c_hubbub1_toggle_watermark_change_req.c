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
typedef  int uint32_t ;
struct hubbub {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL ; 
 int /*<<< orphan*/  DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST ; 
 int /*<<< orphan*/  REG_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  REG_UPDATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void hubbub1_toggle_watermark_change_req(struct hubbub *hubbub)
{
	uint32_t watermark_change_req;

	REG_GET(DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, &watermark_change_req);

	if (watermark_change_req)
		watermark_change_req = 0;
	else
		watermark_change_req = 1;

	REG_UPDATE(DCHUBBUB_ARB_WATERMARK_CHANGE_CNTL,
			DCHUBBUB_ARB_WATERMARK_CHANGE_REQUEST, watermark_change_req);
}