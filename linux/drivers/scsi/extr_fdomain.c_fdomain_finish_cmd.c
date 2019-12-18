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
struct fdomain {TYPE_1__* cur_cmd; scalar_t__ base; } ;
struct TYPE_2__ {int result; int /*<<< orphan*/  (* scsi_done ) (TYPE_1__*) ;} ;

/* Variables and functions */
 scalar_t__ REG_ICTL ; 
 int /*<<< orphan*/  fdomain_make_bus_idle (struct fdomain*) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void fdomain_finish_cmd(struct fdomain *fd, int result)
{
	outb(0, fd->base + REG_ICTL);
	fdomain_make_bus_idle(fd);
	fd->cur_cmd->result = result;
	fd->cur_cmd->scsi_done(fd->cur_cmd);
	fd->cur_cmd = NULL;
}