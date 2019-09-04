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
struct saa7134_dev {int board; struct saa7134_card_ir* remote; } ;
struct TYPE_3__ {scalar_t__ expires; } ;
struct saa7134_card_ir {int running; TYPE_1__ timer; scalar_t__ polling; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ HZ ; 
#define  SAA7134_BOARD_AVERMEDIA_305 144 
#define  SAA7134_BOARD_AVERMEDIA_307 143 
#define  SAA7134_BOARD_AVERMEDIA_505 142 
#define  SAA7134_BOARD_AVERMEDIA_777 141 
#define  SAA7134_BOARD_AVERMEDIA_A16AR 140 
#define  SAA7134_BOARD_AVERMEDIA_A16D 139 
#define  SAA7134_BOARD_AVERMEDIA_GO_007_FM 138 
#define  SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS 137 
#define  SAA7134_BOARD_AVERMEDIA_M102 136 
#define  SAA7134_BOARD_AVERMEDIA_STUDIO_305 135 
#define  SAA7134_BOARD_AVERMEDIA_STUDIO_307 134 
#define  SAA7134_BOARD_AVERMEDIA_STUDIO_505 133 
#define  SAA7134_BOARD_AVERMEDIA_STUDIO_507 132 
#define  SAA7134_BOARD_AVERMEDIA_STUDIO_507UA 131 
#define  SAA7134_BOARD_GOTVIEW_7135 130 
#define  SAA7134_BOARD_KWORLD_VSTREAM_XPERT 129 
#define  SAA7134_BOARD_MD2819 128 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPMODE1 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS0 ; 
 int /*<<< orphan*/  SAA7134_GPIO_GPSTATUS1 ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  saa7134_input_timer ; 
 int /*<<< orphan*/  saa_setb (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __saa7134_ir_start(void *priv)
{
	struct saa7134_dev *dev = priv;
	struct saa7134_card_ir *ir;

	if (!dev || !dev->remote)
		return -EINVAL;

	ir  = dev->remote;
	if (ir->running)
		return 0;

	/* Moved here from saa7134_input_init1() because the latter
	 * is not called on device resume */
	switch (dev->board) {
	case SAA7134_BOARD_MD2819:
	case SAA7134_BOARD_KWORLD_VSTREAM_XPERT:
	case SAA7134_BOARD_AVERMEDIA_305:
	case SAA7134_BOARD_AVERMEDIA_307:
	case SAA7134_BOARD_AVERMEDIA_505:
	case SAA7134_BOARD_AVERMEDIA_STUDIO_305:
	case SAA7134_BOARD_AVERMEDIA_STUDIO_505:
	case SAA7134_BOARD_AVERMEDIA_STUDIO_307:
	case SAA7134_BOARD_AVERMEDIA_STUDIO_507:
	case SAA7134_BOARD_AVERMEDIA_STUDIO_507UA:
	case SAA7134_BOARD_AVERMEDIA_GO_007_FM:
	case SAA7134_BOARD_AVERMEDIA_M102:
	case SAA7134_BOARD_AVERMEDIA_GO_007_FM_PLUS:
		/* Without this we won't receive key up events */
		saa_setb(SAA7134_GPIO_GPMODE0, 0x4);
		saa_setb(SAA7134_GPIO_GPSTATUS0, 0x4);
		break;
	case SAA7134_BOARD_AVERMEDIA_777:
	case SAA7134_BOARD_AVERMEDIA_A16AR:
		/* Without this we won't receive key up events */
		saa_setb(SAA7134_GPIO_GPMODE1, 0x1);
		saa_setb(SAA7134_GPIO_GPSTATUS1, 0x1);
		break;
	case SAA7134_BOARD_AVERMEDIA_A16D:
		/* Without this we won't receive key up events */
		saa_setb(SAA7134_GPIO_GPMODE1, 0x1);
		saa_setb(SAA7134_GPIO_GPSTATUS1, 0x1);
		break;
	case SAA7134_BOARD_GOTVIEW_7135:
		saa_setb(SAA7134_GPIO_GPMODE1, 0x80);
		break;
	}

	ir->running = true;

	if (ir->polling) {
		timer_setup(&ir->timer, saa7134_input_timer, 0);
		ir->timer.expires = jiffies + HZ;
		add_timer(&ir->timer);
	}

	return 0;
}