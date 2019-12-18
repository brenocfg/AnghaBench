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
typedef  int /*<<< orphan*/  u16 ;
struct subchannel_id {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  supported_funcs; } ;
struct TYPE_4__ {TYPE_1__ sbp; } ;
struct qeth_card {TYPE_2__ options; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 struct ccw_device* CARD_DDEV (struct qeth_card*) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  anev_reset ; 
 int /*<<< orphan*/  ccw_device_get_schid (struct ccw_device*,struct subchannel_id*) ; 
 int qdio_pnso_brinfo (struct subchannel_id,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qeth_card*) ; 
 int qeth_anset_makerc (struct qeth_card*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qeth_bridge_emit_host_event (struct qeth_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * qeth_bridgeport_an_set_cb ; 

int qeth_bridgeport_an_set(struct qeth_card *card, int enable)
{
	int rc;
	u16 response;
	struct ccw_device *ddev;
	struct subchannel_id schid;

	if (!card)
		return -EINVAL;
	if (!card->options.sbp.supported_funcs)
		return -EOPNOTSUPP;
	ddev = CARD_DDEV(card);
	ccw_device_get_schid(ddev, &schid);

	if (enable) {
		qeth_bridge_emit_host_event(card, anev_reset, 0, NULL, NULL);
		rc = qdio_pnso_brinfo(schid, 1, &response,
			qeth_bridgeport_an_set_cb, card);
	} else
		rc = qdio_pnso_brinfo(schid, 0, &response, NULL, NULL);
	return qeth_anset_makerc(card, rc, response);
}