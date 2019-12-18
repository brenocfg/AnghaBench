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
typedef  int u8 ;
struct request {int dummy; } ;
struct TYPE_2__ {int* cmd; int cmd_len; int /*<<< orphan*/  result; } ;

/* Variables and functions */
 int /*<<< orphan*/  ILLEGAL_REQUEST ; 
 int MODE_SELECT ; 
 int MODE_SENSE ; 
 int READ_10 ; 
 int READ_6 ; 
 int WRITE_6 ; 
 TYPE_1__* scsi_req (struct request*) ; 

__attribute__((used)) static bool ide_cdrom_prep_pc(struct request *rq)
{
	u8 *c = scsi_req(rq)->cmd;

	/* transform 6-byte read/write commands to the 10-byte version */
	if (c[0] == READ_6 || c[0] == WRITE_6) {
		c[8] = c[4];
		c[5] = c[3];
		c[4] = c[2];
		c[3] = c[1] & 0x1f;
		c[2] = 0;
		c[1] &= 0xe0;
		c[0] += (READ_10 - READ_6);
		scsi_req(rq)->cmd_len = 10;
		return true;
	}

	/*
	 * it's silly to pretend we understand 6-byte sense commands, just
	 * reject with ILLEGAL_REQUEST and the caller should take the
	 * appropriate action
	 */
	if (c[0] == MODE_SENSE || c[0] == MODE_SELECT) {
		scsi_req(rq)->result = ILLEGAL_REQUEST;
		return false;
	}

	return true;
}