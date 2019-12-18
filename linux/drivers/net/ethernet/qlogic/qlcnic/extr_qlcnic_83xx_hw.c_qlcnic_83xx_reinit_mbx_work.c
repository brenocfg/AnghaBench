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
struct qlcnic_mailbox {int /*<<< orphan*/  status; int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  QLC_83XX_MBX_READY ; 
 int /*<<< orphan*/  reinit_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void qlcnic_83xx_reinit_mbx_work(struct qlcnic_mailbox *mbx)
{
	reinit_completion(&mbx->completion);
	set_bit(QLC_83XX_MBX_READY, &mbx->status);
}