#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct scsi_cmnd {int* cmnd; TYPE_1__* device; } ;
struct TYPE_5__ {int this_id; int boot_ldrv; scalar_t__ read_ldidmap; scalar_t__ support_random_del; scalar_t__ boot_ldrv_enabled; } ;
typedef  TYPE_2__ adapter_t ;
struct TYPE_4__ {int id; } ;

/* Variables and functions */
#define  READ_10 131 
#define  READ_6 130 
#define  WRITE_10 129 
#define  WRITE_6 128 

__attribute__((used)) static inline int
mega_get_ldrv_num(adapter_t *adapter, struct scsi_cmnd *cmd, int channel)
{
	int		tgt;
	int		ldrv_num;

	tgt = cmd->device->id;
	
	if ( tgt > adapter->this_id )
		tgt--;	/* we do not get inquires for initiator id */

	ldrv_num = (channel * 15) + tgt;


	/*
	 * If we have a logical drive with boot enabled, project it first
	 */
	if( adapter->boot_ldrv_enabled ) {
		if( ldrv_num == 0 ) {
			ldrv_num = adapter->boot_ldrv;
		}
		else {
			if( ldrv_num <= adapter->boot_ldrv ) {
				ldrv_num--;
			}
		}
	}

	/*
	 * If "delete logical drive" feature is enabled on this controller.
	 * Do only if at least one delete logical drive operation was done.
	 *
	 * Also, after logical drive deletion, instead of logical drive number,
	 * the value returned should be 0x80+logical drive id.
	 *
	 * These is valid only for IO commands.
	 */

	if (adapter->support_random_del && adapter->read_ldidmap )
		switch (cmd->cmnd[0]) {
		case READ_6:	/* fall through */
		case WRITE_6:	/* fall through */
		case READ_10:	/* fall through */
		case WRITE_10:
			ldrv_num += 0x80;
		}

	return ldrv_num;
}