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
struct dvb_net_ule_handle {int* ts; int ts_remain; int* from_where; TYPE_1__* priv; scalar_t__ skipped; } ;
struct TYPE_2__ {int tscc; int /*<<< orphan*/  ts_count; } ;

/* Variables and functions */
 int TS_PUSI ; 
 int /*<<< orphan*/  TS_SZ ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dvb_net_ule_ts_pusi(struct dvb_net_ule_handle *h)
{
	if (h->ts[1] & TS_PUSI) {
		/* Find beginning of first ULE SNDU in current TS cell. */
		/* Synchronize continuity counter. */
		h->priv->tscc = h->ts[3] & 0x0F;
		/* There is a pointer field here. */
		if (h->ts[4] > h->ts_remain) {
			pr_err("%lu: Invalid ULE packet (pointer field %d)\n",
				h->priv->ts_count, h->ts[4]);
			h->ts += TS_SZ;
			h->priv->ts_count++;
			return 1;
		}
		/* Skip to destination of pointer field. */
		h->from_where = &h->ts[5] + h->ts[4];
		h->ts_remain -= 1 + h->ts[4];
		h->skipped = 0;
	} else {
		h->skipped++;
		h->ts += TS_SZ;
		h->priv->ts_count++;
		return 1;
	}

	return 0;
}