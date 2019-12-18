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
struct cx8802_dev {int ts_gen_cntrl; } ;
struct TYPE_2__ {struct cx8802_dev* priv; } ;

/* Variables and functions */

__attribute__((used)) static int or51132_set_ts_param(struct dvb_frontend *fe, int is_punctured)
{
	struct cx8802_dev *dev = fe->dvb->priv;

	dev->ts_gen_cntrl = is_punctured ? 0x04 : 0x00;
	return 0;
}