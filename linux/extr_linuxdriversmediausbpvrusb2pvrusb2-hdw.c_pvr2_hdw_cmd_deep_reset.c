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
struct pvr2_hdw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FX2CMD_DEEP_RESET ; 
 int pvr2_issue_simple_cmd (struct pvr2_hdw*,int /*<<< orphan*/ ) ; 

int pvr2_hdw_cmd_deep_reset(struct pvr2_hdw *hdw)
{
	return pvr2_issue_simple_cmd(hdw,FX2CMD_DEEP_RESET);
}