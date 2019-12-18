#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * body; } ;
struct TYPE_6__ {TYPE_2__ ssid; int /*<<< orphan*/  channel; } ;
struct ks_wlan_private {TYPE_3__ reg; } ;
struct TYPE_4__ {int /*<<< orphan*/ * body; int /*<<< orphan*/  size; } ;
struct hostif_adhoc_set_request {TYPE_1__ ssid; int /*<<< orphan*/  channel; int /*<<< orphan*/  request; } ;

/* Variables and functions */
 int /*<<< orphan*/  HIF_ADH_SET_REQ ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 struct hostif_adhoc_set_request* hostif_generic_request (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_request (struct ks_wlan_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request_to_device (struct ks_wlan_private*,struct hostif_adhoc_set_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void hostif_adhoc_set_request(struct ks_wlan_private *priv)
{
	struct hostif_adhoc_set_request *pp;

	pp = hostif_generic_request(sizeof(*pp), HIF_ADH_SET_REQ);
	if (!pp)
		return;

	init_request(priv, &pp->request);
	pp->channel = cpu_to_le16(priv->reg.channel);
	pp->ssid.size = priv->reg.ssid.size;
	memcpy(&pp->ssid.body[0], &priv->reg.ssid.body[0], priv->reg.ssid.size);

	send_request_to_device(priv, pp, hif_align_size(sizeof(*pp)));
}