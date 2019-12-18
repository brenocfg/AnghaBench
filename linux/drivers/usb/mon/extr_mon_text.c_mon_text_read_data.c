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
struct mon_event_text {int length; scalar_t__ data_flag; int* data; } ;

/* Variables and functions */
 int DATA_MAX ; 
 scalar_t__ snprintf (scalar_t__,scalar_t__,char*,...) ; 

__attribute__((used)) static void mon_text_read_data(struct mon_reader_text *rp,
    struct mon_text_ptr *p, const struct mon_event_text *ep)
{
	int data_len, i;

	if ((data_len = ep->length) > 0) {
		if (ep->data_flag == 0) {
			p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
			    " =");
			if (data_len >= DATA_MAX)
				data_len = DATA_MAX;
			for (i = 0; i < data_len; i++) {
				if (i % 4 == 0) {
					p->cnt += snprintf(p->pbuf + p->cnt,
					    p->limit - p->cnt,
					    " ");
				}
				p->cnt += snprintf(p->pbuf + p->cnt,
				    p->limit - p->cnt,
				    "%02x", ep->data[i]);
			}
			p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
			    "\n");
		} else {
			p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt,
			    " %c\n", ep->data_flag);
		}
	} else {
		p->cnt += snprintf(p->pbuf + p->cnt, p->limit - p->cnt, "\n");
	}
}