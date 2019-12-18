#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int subopcode; int /*<<< orphan*/  opcode; int /*<<< orphan*/  cmd; } ;
typedef  TYPE_2__ megacmd_t ;
struct TYPE_10__ {int read_ldidmap; TYPE_1__* dev; } ;
typedef  TYPE_3__ adapter_t ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_DEL_LOGDRV ; 
 int /*<<< orphan*/  OP_DEL_LOGDRV ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int) ; 
 int mega_internal_command (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mega_do_del_logdrv(adapter_t *adapter, int logdrv)
{
	megacmd_t	mc;
	int	rval;

	memset( &mc, 0, sizeof(megacmd_t));

	mc.cmd = FC_DEL_LOGDRV;
	mc.opcode = OP_DEL_LOGDRV;
	mc.subopcode = logdrv;

	rval = mega_internal_command(adapter, &mc, NULL);

	/* log this event */
	if(rval) {
		dev_warn(&adapter->dev->dev, "Delete LD-%d failed", logdrv);
		return rval;
	}

	/*
	 * After deleting first logical drive, the logical drives must be
	 * addressed by adding 0x80 to the logical drive id.
	 */
	adapter->read_ldidmap = 1;

	return rval;
}