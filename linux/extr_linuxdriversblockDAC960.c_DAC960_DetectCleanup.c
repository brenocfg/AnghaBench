#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int HardwareType; size_t ControllerNumber; scalar_t__* disks; int /*<<< orphan*/  PCIDevice; scalar_t__ IO_Address; scalar_t__ IRQ_Channel; scalar_t__ MemoryMappedAddress; int /*<<< orphan*/  BaseAddress; int /*<<< orphan*/  DmaPages; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
#define  DAC960_BA_Controller 134 
 int /*<<< orphan*/  DAC960_BA_DisableInterrupts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** DAC960_Controllers ; 
#define  DAC960_GEM_Controller 133 
 int /*<<< orphan*/  DAC960_GEM_DisableInterrupts (int /*<<< orphan*/ ) ; 
#define  DAC960_LA_Controller 132 
 int /*<<< orphan*/  DAC960_LA_DisableInterrupts (int /*<<< orphan*/ ) ; 
#define  DAC960_LP_Controller 131 
 int /*<<< orphan*/  DAC960_LP_DisableInterrupts (int /*<<< orphan*/ ) ; 
 int DAC960_MaxLogicalDrives ; 
#define  DAC960_PD_Controller 130 
 int /*<<< orphan*/  DAC960_PD_DisableInterrupts (int /*<<< orphan*/ ) ; 
#define  DAC960_PG_Controller 129 
 int /*<<< orphan*/  DAC960_PG_DisableInterrupts (int /*<<< orphan*/ ) ; 
#define  DAC960_P_Controller 128 
 int /*<<< orphan*/  free_dma_loaf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_irq (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  iounmap (scalar_t__) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 
 int /*<<< orphan*/  pci_disable_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (scalar_t__) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 

__attribute__((used)) static void DAC960_DetectCleanup(DAC960_Controller_T *Controller)
{
  int i;

  /* Free the memory mailbox, status, and related structures */
  free_dma_loaf(Controller->PCIDevice, &Controller->DmaPages);
  if (Controller->MemoryMappedAddress) {
  	switch(Controller->HardwareType)
  	{
		case DAC960_GEM_Controller:
			DAC960_GEM_DisableInterrupts(Controller->BaseAddress);
			break;
		case DAC960_BA_Controller:
			DAC960_BA_DisableInterrupts(Controller->BaseAddress);
			break;
		case DAC960_LP_Controller:
			DAC960_LP_DisableInterrupts(Controller->BaseAddress);
			break;
		case DAC960_LA_Controller:
			DAC960_LA_DisableInterrupts(Controller->BaseAddress);
			break;
		case DAC960_PG_Controller:
			DAC960_PG_DisableInterrupts(Controller->BaseAddress);
			break;
		case DAC960_PD_Controller:
			DAC960_PD_DisableInterrupts(Controller->BaseAddress);
			break;
		case DAC960_P_Controller:
			DAC960_PD_DisableInterrupts(Controller->BaseAddress);
			break;
  	}
  	iounmap(Controller->MemoryMappedAddress);
  }
  if (Controller->IRQ_Channel)
  	free_irq(Controller->IRQ_Channel, Controller);
  if (Controller->IO_Address)
	release_region(Controller->IO_Address, 0x80);
  pci_disable_device(Controller->PCIDevice);
  for (i = 0; (i < DAC960_MaxLogicalDrives) && Controller->disks[i]; i++)
       put_disk(Controller->disks[i]);
  DAC960_Controllers[Controller->ControllerNumber] = NULL;
  kfree(Controller);
}