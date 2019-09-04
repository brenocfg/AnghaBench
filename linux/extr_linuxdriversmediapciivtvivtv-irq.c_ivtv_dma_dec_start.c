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
struct TYPE_2__ {scalar_t__ bytesused; } ;
struct ivtv_stream {int sg_pending_size; int sg_processing_size; int /*<<< orphan*/  type; int /*<<< orphan*/  name; scalar_t__ sg_processed; int /*<<< orphan*/  sg_pending; int /*<<< orphan*/  sg_processing; int /*<<< orphan*/  dma_xfer_cnt; TYPE_1__ q_predma; int /*<<< orphan*/  q_dma; struct ivtv* itv; } ;
struct ivtv_sg_host_element {int dummy; } ;
struct ivtv {int /*<<< orphan*/  cur_dma_stream; int /*<<< orphan*/  i_flags; scalar_t__ dma_retries; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_DEBUG_HI_DMA (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IVTV_F_I_DMA ; 
 int /*<<< orphan*/  ivtv_dma_dec_start_xfer (struct ivtv_stream*) ; 
 int /*<<< orphan*/  ivtv_queue_move (struct ivtv_stream*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ivtv_dma_dec_start(struct ivtv_stream *s)
{
	struct ivtv *itv = s->itv;

	if (s->q_predma.bytesused)
		ivtv_queue_move(s, &s->q_predma, NULL, &s->q_dma, s->q_predma.bytesused);
	s->dma_xfer_cnt++;
	memcpy(s->sg_processing, s->sg_pending, sizeof(struct ivtv_sg_host_element) * s->sg_pending_size);
	s->sg_processing_size = s->sg_pending_size;
	s->sg_pending_size = 0;
	s->sg_processed = 0;

	IVTV_DEBUG_HI_DMA("start DMA for %s\n", s->name);
	itv->dma_retries = 0;
	ivtv_dma_dec_start_xfer(s);
	set_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = s->type;
}