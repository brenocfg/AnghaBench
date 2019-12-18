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
typedef  int u16 ;
struct fmdev {int dummy; } ;
typedef  int /*<<< orphan*/  payload ;

/* Variables and functions */
 int /*<<< orphan*/  FM_AF_JUMP_HANDLE_SETPI_MASK_RESP_IDX ; 
 int /*<<< orphan*/  RDS_PI_MASK_SET ; 
 int /*<<< orphan*/  REG_WR ; 
 int /*<<< orphan*/  fm_irq_timeout_stage (struct fmdev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm_send_cmd (struct fmdev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fm_irq_afjump_set_pimask(struct fmdev *fmdev)
{
	u16 payload;

	payload = 0x0000;
	if (!fm_send_cmd(fmdev, RDS_PI_MASK_SET, REG_WR, &payload, sizeof(payload), NULL))
		fm_irq_timeout_stage(fmdev, FM_AF_JUMP_HANDLE_SETPI_MASK_RESP_IDX);
}