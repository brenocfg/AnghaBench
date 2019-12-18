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
struct adb_request {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADBREQ_SYNC ; 
 int /*<<< orphan*/  ADB_FLUSH (int) ; 
 int /*<<< orphan*/  ADB_WRITEREG (int,int) ; 
 int /*<<< orphan*/  adb_request (struct adb_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
init_turbomouse(int id)
{
	struct adb_request req;

	adb_request(&req, NULL, ADBREQ_SYNC, 1, ADB_FLUSH(id));

	adb_request(&req, NULL, ADBREQ_SYNC, 1, ADB_FLUSH(3));

	adb_request(&req, NULL, ADBREQ_SYNC, 9,
	ADB_WRITEREG(3,2),
	    0xe7,
	    0x8c,
	    0,
	    0,
	    0,
	    0xff,
	    0xff,
	    0x94);

	adb_request(&req, NULL, ADBREQ_SYNC, 1, ADB_FLUSH(3));

	adb_request(&req, NULL, ADBREQ_SYNC, 9,
	ADB_WRITEREG(3,2),
	    0xa5,
	    0x14,
	    0,
	    0,
	    0x69,
	    0xff,
	    0xff,
	    0x27);
}