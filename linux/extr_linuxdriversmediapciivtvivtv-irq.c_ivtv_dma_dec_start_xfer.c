#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ivtv_stream {size_t sg_processed; int /*<<< orphan*/  sg_handle; TYPE_2__* sg_processing; TYPE_1__* sg_dma; struct ivtv* itv; } ;
struct TYPE_6__ {scalar_t__ expires; } ;
struct ivtv {TYPE_3__ dma_timer; } ;
struct TYPE_5__ {int src; int dst; int size; } ;
struct TYPE_4__ {void* size; void* dst; void* src; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_REG_DECDMAADDR ; 
 int /*<<< orphan*/  IVTV_REG_DMAXFER ; 
 int /*<<< orphan*/  add_timer (TYPE_3__*) ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  ivtv_stream_sync_for_device (struct ivtv_stream*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_reg_sync (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ivtv_dma_dec_start_xfer(struct ivtv_stream *s)
{
	struct ivtv *itv = s->itv;

	s->sg_dma->src = cpu_to_le32(s->sg_processing[s->sg_processed].src);
	s->sg_dma->dst = cpu_to_le32(s->sg_processing[s->sg_processed].dst);
	s->sg_dma->size = cpu_to_le32(s->sg_processing[s->sg_processed].size | 0x80000000);
	s->sg_processed++;
	/* Sync Hardware SG List of buffers */
	ivtv_stream_sync_for_device(s);
	write_reg(s->sg_handle, IVTV_REG_DECDMAADDR);
	write_reg_sync(read_reg(IVTV_REG_DMAXFER) | 0x01, IVTV_REG_DMAXFER);
	itv->dma_timer.expires = jiffies + msecs_to_jiffies(300);
	add_timer(&itv->dma_timer);
}