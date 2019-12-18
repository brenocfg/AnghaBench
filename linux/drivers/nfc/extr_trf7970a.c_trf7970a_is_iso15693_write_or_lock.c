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

/* Variables and functions */
#define  ISO15693_CMD_LOCK_AFI 134 
#define  ISO15693_CMD_LOCK_BLOCK 133 
#define  ISO15693_CMD_LOCK_DSFID 132 
#define  ISO15693_CMD_WRITE_AFI 131 
#define  ISO15693_CMD_WRITE_DSFID 130 
#define  ISO15693_CMD_WRITE_MULTIPLE_BLOCK 129 
#define  ISO15693_CMD_WRITE_SINGLE_BLOCK 128 

__attribute__((used)) static int trf7970a_is_iso15693_write_or_lock(u8 cmd)
{
	switch (cmd) {
	case ISO15693_CMD_WRITE_SINGLE_BLOCK:
	case ISO15693_CMD_LOCK_BLOCK:
	case ISO15693_CMD_WRITE_MULTIPLE_BLOCK:
	case ISO15693_CMD_WRITE_AFI:
	case ISO15693_CMD_LOCK_AFI:
	case ISO15693_CMD_WRITE_DSFID:
	case ISO15693_CMD_LOCK_DSFID:
		return 1;
		break;
	default:
		return 0;
	}
}