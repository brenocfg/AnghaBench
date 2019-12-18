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
struct TYPE_2__ {int len; int /*<<< orphan*/  type; } ;
struct hvsi_query {TYPE_1__ hdr; int /*<<< orphan*/  verb; } ;
struct hvsi_priv {scalar_t__ mctrl_update; int /*<<< orphan*/  established; int /*<<< orphan*/  termno; } ;

/* Variables and functions */
 int EIO ; 
 int ENXIO ; 
 int /*<<< orphan*/  VSV_SEND_MODEM_CTL_STATUS ; 
 int /*<<< orphan*/  VS_QUERY_PACKET_HEADER ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hvsi_get_packet (struct hvsi_priv*) ; 
 int hvsi_send_packet (struct hvsi_priv*,TYPE_1__*) ; 
 int /*<<< orphan*/  maybe_msleep (int) ; 
 int /*<<< orphan*/  pr_devel (char*,int /*<<< orphan*/ ,...) ; 

int hvsilib_read_mctrl(struct hvsi_priv *pv)
{
	struct hvsi_query q;
	int rc, timeout;

	pr_devel("HVSI@%x: Querying modem control status...\n",
		 pv->termno);

	pv->mctrl_update = 0;
	q.hdr.type = VS_QUERY_PACKET_HEADER;
	q.hdr.len = sizeof(struct hvsi_query);
	q.verb = cpu_to_be16(VSV_SEND_MODEM_CTL_STATUS);
	rc = hvsi_send_packet(pv, &q.hdr);
	if (rc <= 0) {
		pr_devel("HVSI@%x: Error %d...\n", pv->termno, rc);
		return rc;
	}

	/* Try for up to 200ms */
	for (timeout = 0; timeout < 20; timeout++) {
		if (!pv->established)
			return -ENXIO;
		if (pv->mctrl_update)
			return 0;
		if (!hvsi_get_packet(pv))
			maybe_msleep(10);
	}
	return -EIO;
}