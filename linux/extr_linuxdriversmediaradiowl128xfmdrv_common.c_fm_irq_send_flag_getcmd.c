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
struct fmdev {int dummy; } ;
typedef  int /*<<< orphan*/  flag ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_GET ; 
 int /*<<< orphan*/  FM_HANDLE_FLAG_GETCMD_RESP_IDX ; 
 int /*<<< orphan*/  REG_RD ; 
 int /*<<< orphan*/  fm_irq_timeout_stage (struct fmdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fm_irq_send_flag_getcmd(struct fmdev *fmdev)
{
	u16 flag;

	/* Send FLAG_GET command , to know the source of interrupt */
	if (!fm_send_cmd(fmdev, FLAG_GET, REG_RD, NULL, sizeof(flag), NULL))
		fm_irq_timeout_stage(fmdev, FM_HANDLE_FLAG_GETCMD_RESP_IDX);
}