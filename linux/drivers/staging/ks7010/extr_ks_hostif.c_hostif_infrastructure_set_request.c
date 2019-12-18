#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * body; } ;
struct TYPE_7__ {scalar_t__ phy_type; int /*<<< orphan*/  authenticate_type; int /*<<< orphan*/  beacon_lost_count; TYPE_2__ ssid; } ;
struct ks_wlan_private {TYPE_3__ reg; } ;
struct TYPE_8__ {int* body; int size; } ;
struct TYPE_5__ {int /*<<< orphan*/ * body; int /*<<< orphan*/  size; } ;
struct hostif_infrastructure_set_request {TYPE_4__ channel_list; void* auth_type; void* beacon_lost_count; TYPE_1__ ssid; int /*<<< orphan*/  request; } ;

/* Variables and functions */
 scalar_t__ D_11G_ONLY_MODE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hif_align_size (int) ; 
 struct hostif_infrastructure_set_request* hostif_generic_request (int,int) ; 
 int /*<<< orphan*/  init_request (struct ks_wlan_private*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_request_to_device (struct ks_wlan_private*,struct hostif_infrastructure_set_request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void hostif_infrastructure_set_request(struct ks_wlan_private *priv, int event)
{
	struct hostif_infrastructure_set_request *pp;

	pp = hostif_generic_request(sizeof(*pp), event);
	if (!pp)
		return;

	init_request(priv, &pp->request);
	pp->ssid.size = priv->reg.ssid.size;
	memcpy(&pp->ssid.body[0], &priv->reg.ssid.body[0], priv->reg.ssid.size);
	pp->beacon_lost_count =
	    cpu_to_le16(priv->reg.beacon_lost_count);
	pp->auth_type = cpu_to_le16(priv->reg.authenticate_type);

	pp->channel_list.body[0] = 1;
	pp->channel_list.body[1] = 8;
	pp->channel_list.body[2] = 2;
	pp->channel_list.body[3] = 9;
	pp->channel_list.body[4] = 3;
	pp->channel_list.body[5] = 10;
	pp->channel_list.body[6] = 4;
	pp->channel_list.body[7] = 11;
	pp->channel_list.body[8] = 5;
	pp->channel_list.body[9] = 12;
	pp->channel_list.body[10] = 6;
	pp->channel_list.body[11] = 13;
	pp->channel_list.body[12] = 7;
	if (priv->reg.phy_type == D_11G_ONLY_MODE) {
		pp->channel_list.size = 13;
	} else {
		pp->channel_list.body[13] = 14;
		pp->channel_list.size = 14;
	}

	send_request_to_device(priv, pp, hif_align_size(sizeof(*pp)));
}