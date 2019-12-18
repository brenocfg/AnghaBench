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
typedef  int /*<<< orphan*/  u32 ;
struct ucc_slow_private {struct ucc_slow_info* us_info; } ;
struct ucc_slow_info {int /*<<< orphan*/  ucc_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  QE_CR_PROTOCOL_UNSPECIFIED ; 
 int /*<<< orphan*/  QE_STOP_TX ; 
 int /*<<< orphan*/  qe_issue_cmd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucc_slow_get_qe_cr_subblock (int /*<<< orphan*/ ) ; 

void ucc_slow_stop_tx(struct ucc_slow_private * uccs)
{
	struct ucc_slow_info *us_info = uccs->us_info;
	u32 id;

	id = ucc_slow_get_qe_cr_subblock(us_info->ucc_num);
	qe_issue_cmd(QE_STOP_TX, id, QE_CR_PROTOCOL_UNSPECIFIED, 0);
}