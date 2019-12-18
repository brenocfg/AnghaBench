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
struct airo_info {TYPE_1__* dev; int /*<<< orphan*/  flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMAND ; 
 int EIO ; 
 int /*<<< orphan*/  FLAG_FLASHING ; 
 int FLASH_COMMAND ; 
 int /*<<< orphan*/  OUT4500 (struct airo_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SWS0 ; 
 int /*<<< orphan*/  SWS1 ; 
 int /*<<< orphan*/  SWS2 ; 
 int /*<<< orphan*/  SWS3 ; 
 int /*<<< orphan*/  airo_print_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 scalar_t__ probe ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  waitbusy (struct airo_info*) ; 

__attribute__((used)) static int setflashmode (struct airo_info *ai) {
	set_bit (FLAG_FLASHING, &ai->flags);

	OUT4500(ai, SWS0, FLASH_COMMAND);
	OUT4500(ai, SWS1, FLASH_COMMAND);
	if (probe) {
		OUT4500(ai, SWS0, FLASH_COMMAND);
		OUT4500(ai, COMMAND,0x10);
	} else {
		OUT4500(ai, SWS2, FLASH_COMMAND);
		OUT4500(ai, SWS3, FLASH_COMMAND);
		OUT4500(ai, COMMAND,0);
	}
	msleep(500);		/* 500ms delay */

	if(!waitbusy(ai)) {
		clear_bit (FLAG_FLASHING, &ai->flags);
		airo_print_info(ai->dev->name, "Waitbusy hang after setflash mode");
		return -EIO;
	}
	return 0;
}