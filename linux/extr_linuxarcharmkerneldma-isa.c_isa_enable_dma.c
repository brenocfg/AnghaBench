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
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;
struct TYPE_4__ {int length; unsigned long dma_address; } ;
struct TYPE_5__ {unsigned int dma_mode; int sgcount; int count; scalar_t__ invalid; TYPE_1__ buf; int /*<<< orphan*/  addr; TYPE_1__* sg; } ;
typedef  TYPE_2__ dma_t ;

/* Variables and functions */
 int DMA_BIDIRECTIONAL ; 
 int DMA_FROM_DEVICE ; 
#define  DMA_MODE_CASCADE 130 
 int DMA_MODE_MASK ; 
#define  DMA_MODE_READ 129 
#define  DMA_MODE_WRITE 128 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 size_t ISA_DMA_ADDR ; 
 size_t ISA_DMA_CLRFF ; 
 size_t ISA_DMA_COUNT ; 
 size_t ISA_DMA_MASK ; 
 size_t ISA_DMA_MODE ; 
 size_t ISA_DMA_PGHI ; 
 size_t ISA_DMA_PGLO ; 
 unsigned long dma_map_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ ** isa_dma_port ; 
 int /*<<< orphan*/  outb (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isa_enable_dma(unsigned int chan, dma_t *dma)
{
	if (dma->invalid) {
		unsigned long address, length;
		unsigned int mode;
		enum dma_data_direction direction;

		mode = (chan & 3) | dma->dma_mode;
		switch (dma->dma_mode & DMA_MODE_MASK) {
		case DMA_MODE_READ:
			direction = DMA_FROM_DEVICE;
			break;

		case DMA_MODE_WRITE:
			direction = DMA_TO_DEVICE;
			break;

		case DMA_MODE_CASCADE:
			direction = DMA_BIDIRECTIONAL;
			break;

		default:
			direction = DMA_NONE;
			break;
		}

		if (!dma->sg) {
			/*
			 * Cope with ISA-style drivers which expect cache
			 * coherence.
			 */
			dma->sg = &dma->buf;
			dma->sgcount = 1;
			dma->buf.length = dma->count;
			dma->buf.dma_address = dma_map_single(NULL,
				dma->addr, dma->count,
				direction);
		}

		address = dma->buf.dma_address;
		length  = dma->buf.length - 1;

		outb(address >> 16, isa_dma_port[chan][ISA_DMA_PGLO]);
		outb(address >> 24, isa_dma_port[chan][ISA_DMA_PGHI]);

		if (chan >= 4) {
			address >>= 1;
			length >>= 1;
		}

		outb(0, isa_dma_port[chan][ISA_DMA_CLRFF]);

		outb(address, isa_dma_port[chan][ISA_DMA_ADDR]);
		outb(address >> 8, isa_dma_port[chan][ISA_DMA_ADDR]);

		outb(length, isa_dma_port[chan][ISA_DMA_COUNT]);
		outb(length >> 8, isa_dma_port[chan][ISA_DMA_COUNT]);

		outb(mode, isa_dma_port[chan][ISA_DMA_MODE]);
		dma->invalid = 0;
	}
	outb(chan & 3, isa_dma_port[chan][ISA_DMA_MASK]);
}