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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  nr; } ;
struct bttv {int i2c_done; int /*<<< orphan*/  irq_me; int /*<<< orphan*/  irq_total; TYPE_1__ c; int /*<<< orphan*/  mute; int /*<<< orphan*/  audio_input; scalar_t__ opt_automute; int /*<<< orphan*/  i2c_queue; scalar_t__ remote; int /*<<< orphan*/  field_count; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  BT848_DSTATUS ; 
 int BT848_DSTATUS_HLOC ; 
 int BT848_DSTATUS_NUML ; 
 int BT848_DSTATUS_PRES ; 
 int BT848_INT_FDSR ; 
 int BT848_INT_FMTCHG ; 
 int BT848_INT_GPINT ; 
 int BT848_INT_HLOCK ; 
 int BT848_INT_I2CDONE ; 
 int /*<<< orphan*/  BT848_INT_MASK ; 
 int BT848_INT_OCERR ; 
 int BT848_INT_RISCI ; 
 int BT848_INT_SCERR ; 
 int /*<<< orphan*/  BT848_INT_STAT ; 
 int BT848_INT_VPRES ; 
 int BT848_INT_VSYNC ; 
 int /*<<< orphan*/  BT848_RISC_COUNT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 int /*<<< orphan*/  audio_mux_gpio (struct bttv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btread (int /*<<< orphan*/ ) ; 
 scalar_t__ bttv_debug ; 
 int /*<<< orphan*/  bttv_input_irq (struct bttv*) ; 
 int /*<<< orphan*/  bttv_irq_switch_vbi (struct bttv*) ; 
 int /*<<< orphan*/  bttv_irq_switch_video (struct bttv*) ; 
 int /*<<< orphan*/  bttv_irq_wakeup_top (struct bttv*) ; 
 int /*<<< orphan*/  bttv_print_irqbits (int,int) ; 
 int /*<<< orphan*/  bttv_print_riscaddr (struct bttv*) ; 
 int /*<<< orphan*/  btwrite (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fdsr ; 
 scalar_t__ irq_debug ; 
 int /*<<< orphan*/  pr_cont (char*,...) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t bttv_irq(int irq, void *dev_id)
{
	u32 stat,astat;
	u32 dstat;
	int count;
	struct bttv *btv;
	int handled = 0;

	btv=(struct bttv *)dev_id;

	count=0;
	while (1) {
		/* get/clear interrupt status bits */
		stat=btread(BT848_INT_STAT);
		astat=stat&btread(BT848_INT_MASK);
		if (!astat)
			break;
		handled = 1;
		btwrite(stat,BT848_INT_STAT);

		/* get device status bits */
		dstat=btread(BT848_DSTATUS);

		if (irq_debug) {
			pr_debug("%d: irq loop=%d fc=%d riscs=%x, riscc=%08x, ",
				 btv->c.nr, count, btv->field_count,
				 stat>>28, btread(BT848_RISC_COUNT));
			bttv_print_irqbits(stat,astat);
			if (stat & BT848_INT_HLOCK)
				pr_cont("   HLOC => %s",
					dstat & BT848_DSTATUS_HLOC
					? "yes" : "no");
			if (stat & BT848_INT_VPRES)
				pr_cont("   PRES => %s",
					dstat & BT848_DSTATUS_PRES
					? "yes" : "no");
			if (stat & BT848_INT_FMTCHG)
				pr_cont("   NUML => %s",
					dstat & BT848_DSTATUS_NUML
					? "625" : "525");
			pr_cont("\n");
		}

		if (astat&BT848_INT_VSYNC)
			btv->field_count++;

		if ((astat & BT848_INT_GPINT) && btv->remote) {
			bttv_input_irq(btv);
		}

		if (astat & BT848_INT_I2CDONE) {
			btv->i2c_done = stat;
			wake_up(&btv->i2c_queue);
		}

		if ((astat & BT848_INT_RISCI)  &&  (stat & (4<<28)))
			bttv_irq_switch_vbi(btv);

		if ((astat & BT848_INT_RISCI)  &&  (stat & (2<<28)))
			bttv_irq_wakeup_top(btv);

		if ((astat & BT848_INT_RISCI)  &&  (stat & (1<<28)))
			bttv_irq_switch_video(btv);

		if ((astat & BT848_INT_HLOCK)  &&  btv->opt_automute)
			/* trigger automute */
			audio_mux_gpio(btv, btv->audio_input, btv->mute);

		if (astat & (BT848_INT_SCERR|BT848_INT_OCERR)) {
			pr_info("%d: %s%s @ %08x,",
				btv->c.nr,
				(astat & BT848_INT_SCERR) ? "SCERR" : "",
				(astat & BT848_INT_OCERR) ? "OCERR" : "",
				btread(BT848_RISC_COUNT));
			bttv_print_irqbits(stat,astat);
			pr_cont("\n");
			if (bttv_debug)
				bttv_print_riscaddr(btv);
		}
		if (fdsr && astat & BT848_INT_FDSR) {
			pr_info("%d: FDSR @ %08x\n",
				btv->c.nr, btread(BT848_RISC_COUNT));
			if (bttv_debug)
				bttv_print_riscaddr(btv);
		}

		count++;
		if (count > 4) {

			if (count > 8 || !(astat & BT848_INT_GPINT)) {
				btwrite(0, BT848_INT_MASK);

				pr_err("%d: IRQ lockup, cleared int mask [",
				       btv->c.nr);
			} else {
				pr_err("%d: IRQ lockup, clearing GPINT from int mask [",
				       btv->c.nr);

				btwrite(btread(BT848_INT_MASK) & (-1 ^ BT848_INT_GPINT),
						BT848_INT_MASK);
			}

			bttv_print_irqbits(stat,astat);

			pr_cont("]\n");
		}
	}
	btv->irq_total++;
	if (handled)
		btv->irq_me++;
	return IRQ_RETVAL(handled);
}