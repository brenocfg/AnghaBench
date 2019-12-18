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
struct adb_request {int reply_len; int* reply; } ;
struct TYPE_2__ {int handler_id; } ;

/* Variables and functions */
 int ADBREQ_REPLY ; 
 int ADBREQ_SYNC ; 
 int /*<<< orphan*/  ADB_READREG (int,int) ; 
 int /*<<< orphan*/  ADB_WRITEREG (int,int) ; 
 TYPE_1__* adb_handler ; 
 int /*<<< orphan*/  adb_request (struct adb_request*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static int try_handler_change(int address, int new_id)
{
	struct adb_request req;

	if (adb_handler[address].handler_id == new_id)
	    return 1;
	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	    ADB_WRITEREG(address, 3), address | 0x20, new_id);
	adb_request(&req, NULL, ADBREQ_SYNC | ADBREQ_REPLY, 1,
	    ADB_READREG(address, 3));
	if (req.reply_len < 2)
	    return 0;
	if (req.reply[2] != new_id)
	    return 0;
	adb_handler[address].handler_id = req.reply[2];

	return 1;
}