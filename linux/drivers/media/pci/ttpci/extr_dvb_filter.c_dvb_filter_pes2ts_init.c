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
struct dvb_filter_pes2ts {unsigned char* buf; void* priv; int /*<<< orphan*/ * cb; scalar_t__ cc; } ;
typedef  int /*<<< orphan*/  dvb_filter_pes2ts_cb_t ;

/* Variables and functions */

void dvb_filter_pes2ts_init(struct dvb_filter_pes2ts *p2ts, unsigned short pid,
			    dvb_filter_pes2ts_cb_t *cb, void *priv)
{
	unsigned char *buf=p2ts->buf;

	buf[0]=0x47;
	buf[1]=(pid>>8);
	buf[2]=pid&0xff;
	p2ts->cc=0;
	p2ts->cb=cb;
	p2ts->priv=priv;
}