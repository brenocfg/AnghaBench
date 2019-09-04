#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pci_device_id {int dummy; } ;
struct pci_dev {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * disks; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 scalar_t__ DAC960_ControllerCount ; 
 int /*<<< orphan*/  DAC960_CreateProcEntries (TYPE_1__*) ; 
 TYPE_1__* DAC960_DetectController (struct pci_dev*,struct pci_device_id const*) ; 
 int /*<<< orphan*/  DAC960_Error (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DAC960_FinalizeController (TYPE_1__*) ; 
 int /*<<< orphan*/  DAC960_InitializeController (TYPE_1__*) ; 
 scalar_t__ DAC960_MaxControllers ; 
 int DAC960_MaxLogicalDrives ; 
 int ENODEV ; 
 int /*<<< orphan*/  add_disk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  disk_size (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_capacity (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int 
DAC960_Probe(struct pci_dev *dev, const struct pci_device_id *entry)
{
  int disk;
  DAC960_Controller_T *Controller;

  if (DAC960_ControllerCount == DAC960_MaxControllers)
  {
	DAC960_Error("More than %d DAC960 Controllers detected - "
                       "ignoring from Controller at\n",
                       NULL, DAC960_MaxControllers);
	return -ENODEV;
  }

  Controller = DAC960_DetectController(dev, entry);
  if (!Controller)
	return -ENODEV;

  if (!DAC960_InitializeController(Controller)) {
  	DAC960_FinalizeController(Controller);
	return -ENODEV;
  }

  for (disk = 0; disk < DAC960_MaxLogicalDrives; disk++) {
        set_capacity(Controller->disks[disk], disk_size(Controller, disk));
        add_disk(Controller->disks[disk]);
  }
  DAC960_CreateProcEntries(Controller);
  return 0;
}