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
typedef  int u8 ;
struct ide_atapi_pc {int* c; int req_xfer; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int GPCMD_FORMAT_UNIT ; 
 int /*<<< orphan*/  PC_FLAG_WRITING ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  ide_init_pc (struct ide_atapi_pc*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_unaligned (int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static void ide_floppy_create_format_unit_cmd(struct ide_atapi_pc *pc,
					      u8 *buf, int b, int l,
					      int flags)
{
	ide_init_pc(pc);
	pc->c[0] = GPCMD_FORMAT_UNIT;
	pc->c[1] = 0x17;

	memset(buf, 0, 12);
	buf[1] = 0xA2;
	/* Default format list header, u8 1: FOV/DCRT/IMM bits set */

	if (flags & 1)				/* Verify bit on... */
		buf[1] ^= 0x20;			/* ... turn off DCRT bit */
	buf[3] = 8;

	put_unaligned(cpu_to_be32(b), (unsigned int *)(&buf[4]));
	put_unaligned(cpu_to_be32(l), (unsigned int *)(&buf[8]));
	pc->req_xfer = 12;
	pc->flags |= PC_FLAG_WRITING;
}