#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int ControllerNumber; int /*<<< orphan*/ ** RequestQueue; int /*<<< orphan*/ * disks; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int DAC960_MAJOR ; 
 int DAC960_MaxLogicalDrives ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unregister_blkdev (int,char*) ; 

__attribute__((used)) static void DAC960_UnregisterBlockDevice(DAC960_Controller_T *Controller)
{
  int MajorNumber = DAC960_MAJOR + Controller->ControllerNumber;
  int disk;

  /* does order matter when deleting gendisk and cleanup in request queue? */
  for (disk = 0; disk < DAC960_MaxLogicalDrives; disk++) {
	del_gendisk(Controller->disks[disk]);
	blk_cleanup_queue(Controller->RequestQueue[disk]);
	Controller->RequestQueue[disk] = NULL;
  }

  /*
    Unregister the Block Device Major Number for this DAC960 Controller.
  */
  unregister_blkdev(MajorNumber, "dac960");
}