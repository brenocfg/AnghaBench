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
struct qedi_dbg_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  QEDI_INFO (struct qedi_dbg_ctx*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  QEDI_LOG_DEBUGFS ; 
 int qedi_do_not_recover ; 

__attribute__((used)) static ssize_t
qedi_dbg_do_not_recover_enable(struct qedi_dbg_ctx *qedi_dbg)
{
	if (!qedi_do_not_recover)
		qedi_do_not_recover = 1;

	QEDI_INFO(qedi_dbg, QEDI_LOG_DEBUGFS, "do_not_recover=%d\n",
		  qedi_do_not_recover);
	return 0;
}