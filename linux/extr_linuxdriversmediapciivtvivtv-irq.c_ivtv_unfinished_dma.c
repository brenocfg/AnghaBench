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
struct timer_list {int dummy; } ;
struct ivtv {int cur_dma_stream; int /*<<< orphan*/  dma_waitq; int /*<<< orphan*/  i_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IVTV_ERR (char*,int,int) ; 
 int /*<<< orphan*/  IVTV_F_I_DMA ; 
 int /*<<< orphan*/  IVTV_F_I_UDMA ; 
 int /*<<< orphan*/  IVTV_REG_DMASTATUS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_timer ; 
 struct ivtv* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct ivtv* itv ; 
 int read_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_reg (int,int /*<<< orphan*/ ) ; 

void ivtv_unfinished_dma(struct timer_list *t)
{
	struct ivtv *itv = from_timer(itv, t, dma_timer);

	if (!test_bit(IVTV_F_I_DMA, &itv->i_flags))
		return;
	IVTV_ERR("DMA TIMEOUT %08x %d\n", read_reg(IVTV_REG_DMASTATUS), itv->cur_dma_stream);

	write_reg(read_reg(IVTV_REG_DMASTATUS) & 3, IVTV_REG_DMASTATUS);
	clear_bit(IVTV_F_I_UDMA, &itv->i_flags);
	clear_bit(IVTV_F_I_DMA, &itv->i_flags);
	itv->cur_dma_stream = -1;
	wake_up(&itv->dma_waitq);
}