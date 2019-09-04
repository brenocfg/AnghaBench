#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ivtv_stream {scalar_t__ dma; scalar_t__ type; struct ivtv* itv; } ;
struct TYPE_4__ {TYPE_1__* sliced_in; } ;
struct ivtv {TYPE_2__ vbi; } ;
struct TYPE_3__ {scalar_t__ service_set; } ;

/* Variables and functions */
 scalar_t__ IVTV_ENC_STREAM_TYPE_VBI ; 
 scalar_t__ PCI_DMA_NONE ; 
 scalar_t__ SLICED_VBI_PIO ; 

__attribute__((used)) static inline int ivtv_use_pio(struct ivtv_stream *s)
{
	struct ivtv *itv = s->itv;

	return s->dma == PCI_DMA_NONE ||
	    (SLICED_VBI_PIO && s->type == IVTV_ENC_STREAM_TYPE_VBI && itv->vbi.sliced_in->service_set);
}