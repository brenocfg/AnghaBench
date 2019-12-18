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
struct mgsl_struct {scalar_t__ bus_type; } ;
struct TYPE_3__ {int /*<<< orphan*/ * virt_addr; int /*<<< orphan*/  dma_addr; } ;
typedef  TYPE_1__ DMABUFFERENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  DMABUFFERSIZE ; 
 scalar_t__ MGSL_BUS_TYPE_PCI ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mgsl_free_frame_memory(struct mgsl_struct *info, DMABUFFERENTRY *BufferList, int Buffercount)
{
	int i;

	if ( BufferList ) {
		for ( i = 0 ; i < Buffercount ; i++ ) {
			if ( BufferList[i].virt_addr ) {
				if ( info->bus_type != MGSL_BUS_TYPE_PCI )
					dma_free_coherent(NULL, DMABUFFERSIZE, BufferList[i].virt_addr, BufferList[i].dma_addr);
				BufferList[i].virt_addr = NULL;
			}
		}
	}

}