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
struct hvsi_priv {size_t inbuf_cur; int inbuf_len; int /*<<< orphan*/  termno; int /*<<< orphan*/  established; int /*<<< orphan*/ * inbuf; scalar_t__ inbuf_pktlen; int /*<<< orphan*/  opened; } ;

/* Variables and functions */
 int ENXIO ; 
 int EPIPE ; 
 scalar_t__ WARN_ON (int) ; 
 scalar_t__ hvsi_get_packet (struct hvsi_priv*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 unsigned int min (int,int) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ) ; 

int hvsilib_get_chars(struct hvsi_priv *pv, char *buf, int count)
{
	unsigned int tries, read = 0;

	if (WARN_ON(!pv))
		return -ENXIO;

	/* If we aren't open, don't do anything in order to avoid races
	 * with connection establishment. The hvc core will call this
	 * before we have returned from notifier_add(), and we need to
	 * avoid multiple users playing with the receive buffer
	 */
	if (!pv->opened)
		return 0;

	/* We try twice, once with what data we have and once more
	 * after we try to fetch some more from the hypervisor
	 */
	for (tries = 1; count && tries < 2; tries++) {
		/* Consume existing data packet */
		if (pv->inbuf_pktlen) {
			unsigned int l = min(count, (int)pv->inbuf_pktlen);
			memcpy(&buf[read], &pv->inbuf[pv->inbuf_cur], l);
			pv->inbuf_cur += l;
			pv->inbuf_pktlen -= l;
			count -= l;
			read += l;
		}
		if (count == 0)
			break;

		/* Data packet fully consumed, move down remaning data */
		if (pv->inbuf_cur) {
			pv->inbuf_len -= pv->inbuf_cur;
			memmove(pv->inbuf, &pv->inbuf[pv->inbuf_cur],
				pv->inbuf_len);
			pv->inbuf_cur = 0;
		}

		/* Try to get another packet */
		if (hvsi_get_packet(pv))
			tries--;
	}
	if (!pv->established) {
		pr_devel("HVSI@%x: returning -EPIPE\n", pv->termno);
		return -EPIPE;
	}
	return read;
}