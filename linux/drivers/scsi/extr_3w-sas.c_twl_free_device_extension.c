#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * event_queue; int /*<<< orphan*/ * sense_buffer_phys; scalar_t__* sense_buffer_virt; TYPE_1__* tw_pci_dev; int /*<<< orphan*/ * generic_buffer_phys; scalar_t__* generic_buffer_virt; int /*<<< orphan*/ * command_packet_phys; scalar_t__* command_packet_virt; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ TW_Device_Extension ;
typedef  int /*<<< orphan*/  TW_Command_Full ;
typedef  int /*<<< orphan*/  TW_Command_Apache_Header ;

/* Variables and functions */
 int TW_Q_LENGTH ; 
 int TW_SECTOR_SIZE ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void twl_free_device_extension(TW_Device_Extension *tw_dev)
{
	if (tw_dev->command_packet_virt[0])
		dma_free_coherent(&tw_dev->tw_pci_dev->dev,
				    sizeof(TW_Command_Full)*TW_Q_LENGTH,
				    tw_dev->command_packet_virt[0],
				    tw_dev->command_packet_phys[0]);

	if (tw_dev->generic_buffer_virt[0])
		dma_free_coherent(&tw_dev->tw_pci_dev->dev,
				    TW_SECTOR_SIZE*TW_Q_LENGTH,
				    tw_dev->generic_buffer_virt[0],
				    tw_dev->generic_buffer_phys[0]);

	if (tw_dev->sense_buffer_virt[0])
		dma_free_coherent(&tw_dev->tw_pci_dev->dev,
				    sizeof(TW_Command_Apache_Header)*
				    TW_Q_LENGTH,
				    tw_dev->sense_buffer_virt[0],
				    tw_dev->sense_buffer_phys[0]);

	kfree(tw_dev->event_queue[0]);
}