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
struct mon_text_ptr {scalar_t__ cnt; scalar_t__ limit; scalar_t__ pbuf; } ;
struct mon_reader_text {int dummy; } ;
struct mon_event_text {char setup_flag; int* setup; char status; } ;

/* Variables and functions */
 scalar_t__ snprintf (scalar_t__,scalar_t__,char*,char,...) ; 

__attribute__((used)) static void mon_text_read_statset(struct mon_reader_text *rp,
	struct mon_text_ptr *p, const struct mon_event_text *ep)
{

	if (ep->setup_flag == 0) {   /* Setup packet is present and captured */
		p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
		    " s %02x %02x %04x %04x %04x",
		    ep->setup[0],
		    ep->setup[1],
		    (ep->setup[3] << 8) | ep->setup[2],
		    (ep->setup[5] << 8) | ep->setup[4],
		    (ep->setup[7] << 8) | ep->setup[6]);
	} else if (ep->setup_flag != '-') { /* Unable to capture setup packet */
		p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
		    " %c __ __ ____ ____ ____", ep->setup_flag);
	} else {                     /* No setup for this kind of URB */
		p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
		    " %d", ep->status);
	}
}