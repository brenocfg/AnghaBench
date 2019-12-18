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
init_microspeed(int id)
{
	struct adb_request req;

	adb_request(&req, NULL, ADBREQ_SYNC, 1, ADB_FLUSH(id));

	/* This will initialize mice using the Microspeed, MacPoint and
	   other compatible firmware. Bit 12 enables extended protocol.
	   
	   Register 1 Listen (4 Bytes)
            0 -  3     Button is mouse (set also for double clicking!!!)
            4 -  7     Button is locking (affects change speed also)
            8 - 11     Button changes speed
           12          1 = Extended mouse mode, 0 = normal mouse mode
           13 - 15     unused 0
           16 - 23     normal speed
           24 - 31     changed speed

       Register 1 talk holds version and product identification information.
       Register 1 Talk (4 Bytes):
            0 -  7     Product code
            8 - 23     undefined, reserved
           24 - 31     Version number
        
       Speed 0 is max. 1 to 255 set speed in increments of 1/256 of max.
 */
	adb_request(&req, NULL, ADBREQ_SYNC, 5,
	ADB_WRITEREG(id,1),
	    0x20,	/* alt speed = 0x20 (rather slow) */
	    0x00,	/* norm speed = 0x00 (fastest) */
	    0x10,	/* extended protocol, no speed change */
	    0x07);	/* all buttons enabled as mouse buttons, no locking */


	adb_request(&req, NULL, ADBREQ_SYNC, 1, ADB_FLUSH(id));
}