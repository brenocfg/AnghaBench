#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_3__ {scalar_t__ cmd_line_ptr; scalar_t__ setup_move_size; } ;
struct TYPE_4__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 scalar_t__ OLD_CL_ADDRESS ; 
 scalar_t__ OLD_CL_MAGIC ; 
 TYPE_2__ boot_params ; 
 int ds () ; 
 int /*<<< orphan*/  hdr ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void copy_boot_params(void)
{
	struct old_cmdline {
		u16 cl_magic;
		u16 cl_offset;
	};
	const struct old_cmdline * const oldcmd =
		(const struct old_cmdline *)OLD_CL_ADDRESS;

	BUILD_BUG_ON(sizeof boot_params != 4096);
	memcpy(&boot_params.hdr, &hdr, sizeof hdr);

	if (!boot_params.hdr.cmd_line_ptr &&
	    oldcmd->cl_magic == OLD_CL_MAGIC) {
		/* Old-style command line protocol. */
		u16 cmdline_seg;

		/* Figure out if the command line falls in the region
		   of memory that an old kernel would have copied up
		   to 0x90000... */
		if (oldcmd->cl_offset < boot_params.hdr.setup_move_size)
			cmdline_seg = ds();
		else
			cmdline_seg = 0x9000;

		boot_params.hdr.cmd_line_ptr =
			(cmdline_seg << 4) + oldcmd->cl_offset;
	}
}