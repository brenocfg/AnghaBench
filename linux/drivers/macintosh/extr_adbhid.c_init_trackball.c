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
 int /*<<< orphan*/  ADB_WRITEREG (int,int) ; 
 int /*<<< orphan*/  adb_request (struct adb_request*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void 
init_trackball(int id)
{
	struct adb_request req;

	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 00,0x81);

	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 01,0x81);

	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 02,0x81);

	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 03,0x38);

	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 00,0x81);

	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 01,0x81);

	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 02,0x81);

	adb_request(&req, NULL, ADBREQ_SYNC, 3,
	ADB_WRITEREG(id,1), 03,0x38);
}