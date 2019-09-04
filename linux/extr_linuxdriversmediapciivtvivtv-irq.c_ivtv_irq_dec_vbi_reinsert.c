#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ivtv_stream {int /*<<< orphan*/  s_flags; } ;
struct ivtv {struct ivtv_stream* streams; } ;

/* Variables and functions */
 int CX2341X_MBOX_MAX_DATA ; 
 int /*<<< orphan*/  IVTV_DEBUG_HI_IRQ (char*) ; 
 size_t IVTV_DEC_STREAM_TYPE_VBI ; 
 int /*<<< orphan*/  IVTV_F_S_CLAIMED ; 
 int /*<<< orphan*/  IVTV_F_S_PIO_PENDING ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stream_enc_dma_append (struct ivtv_stream*,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ivtv_irq_dec_vbi_reinsert(struct ivtv *itv)
{
	u32 data[CX2341X_MBOX_MAX_DATA];
	struct ivtv_stream *s = &itv->streams[IVTV_DEC_STREAM_TYPE_VBI];

	IVTV_DEBUG_HI_IRQ("DEC VBI REINSERT\n");
	if (test_bit(IVTV_F_S_CLAIMED, &s->s_flags) &&
			!stream_enc_dma_append(s, data)) {
		set_bit(IVTV_F_S_PIO_PENDING, &s->s_flags);
	}
}