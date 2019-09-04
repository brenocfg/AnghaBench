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
struct dvb_frontend {TYPE_1__* dvb; } ;
struct dvb_bt8xx_card {int /*<<< orphan*/  bttv_nr; } ;
struct TYPE_2__ {struct dvb_bt8xx_card* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  bttv_gpio_enable (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  bttv_write_gpio (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int pinnsat_tuner_init(struct dvb_frontend* fe)
{
	struct dvb_bt8xx_card *card = fe->dvb->priv;

	bttv_gpio_enable(card->bttv_nr, 1, 1);  /* output */
	bttv_write_gpio(card->bttv_nr, 1, 1);   /* relay on */

	return 0;
}