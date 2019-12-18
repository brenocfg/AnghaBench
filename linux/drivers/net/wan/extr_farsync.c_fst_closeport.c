#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct fst_port_info {scalar_t__ run; TYPE_1__* card; } ;
struct TYPE_2__ {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_OPEN ; 
 scalar_t__ FST_RUNNING ; 
 int OPSTS_DTR ; 
 int OPSTS_RTS ; 
 int /*<<< orphan*/  STOPPORT ; 
 int /*<<< orphan*/  dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fst_issue_cmd (struct fst_port_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fst_op_lower (struct fst_port_info*,int) ; 

__attribute__((used)) static void
fst_closeport(struct fst_port_info *port)
{
	if (port->card->state == FST_RUNNING) {
		if (port->run) {
			port->run = 0;
			fst_op_lower(port, OPSTS_RTS | OPSTS_DTR);

			fst_issue_cmd(port, STOPPORT);
		} else {
			dbg(DBG_OPEN, "close: port not running\n");
		}
	}
}