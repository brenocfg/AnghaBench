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
struct sh_cmt_device {TYPE_2__* pdev; TYPE_1__* info; int /*<<< orphan*/  mapbase; } ;
struct sh_cmt_channel {unsigned int index; unsigned int hwidx; unsigned int timer_bit; int max_match_value; int match_value; int cs_enabled; int /*<<< orphan*/  lock; int /*<<< orphan*/  iostart; int /*<<< orphan*/  ioctrl; struct sh_cmt_device* cmt; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int model; int width; } ;

/* Variables and functions */
#define  SH_CMT0_RCAR_GEN2 132 
#define  SH_CMT1_RCAR_GEN2 131 
#define  SH_CMT_16BIT 130 
#define  SH_CMT_32BIT 129 
#define  SH_CMT_48BIT 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_lock_init (int /*<<< orphan*/ *) ; 
 int sh_cmt_register (struct sh_cmt_channel*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sh_cmt_setup_channel(struct sh_cmt_channel *ch, unsigned int index,
				unsigned int hwidx, bool clockevent,
				bool clocksource, struct sh_cmt_device *cmt)
{
	int ret;

	/* Skip unused channels. */
	if (!clockevent && !clocksource)
		return 0;

	ch->cmt = cmt;
	ch->index = index;
	ch->hwidx = hwidx;
	ch->timer_bit = hwidx;

	/*
	 * Compute the address of the channel control register block. For the
	 * timers with a per-channel start/stop register, compute its address
	 * as well.
	 */
	switch (cmt->info->model) {
	case SH_CMT_16BIT:
		ch->ioctrl = cmt->mapbase + 2 + ch->hwidx * 6;
		break;
	case SH_CMT_32BIT:
	case SH_CMT_48BIT:
		ch->ioctrl = cmt->mapbase + 0x10 + ch->hwidx * 0x10;
		break;
	case SH_CMT0_RCAR_GEN2:
	case SH_CMT1_RCAR_GEN2:
		ch->iostart = cmt->mapbase + ch->hwidx * 0x100;
		ch->ioctrl = ch->iostart + 0x10;
		ch->timer_bit = 0;
		break;
	}

	if (cmt->info->width == (sizeof(ch->max_match_value) * 8))
		ch->max_match_value = ~0;
	else
		ch->max_match_value = (1 << cmt->info->width) - 1;

	ch->match_value = ch->max_match_value;
	raw_spin_lock_init(&ch->lock);

	ret = sh_cmt_register(ch, dev_name(&cmt->pdev->dev),
			      clockevent, clocksource);
	if (ret) {
		dev_err(&cmt->pdev->dev, "ch%u: registration failed\n",
			ch->index);
		return ret;
	}
	ch->cs_enabled = false;

	return 0;
}