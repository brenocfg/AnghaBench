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
typedef  int /*<<< orphan*/  u8 ;
struct mrvl_ie_header {void* len; void* type; } ;
struct lbs_private {int scan_channel; TYPE_2__* scan_req; } ;
struct TYPE_6__ {int passivescan; } ;
struct chanscanparamset {void* maxscantime; TYPE_3__ chanscanmode; int /*<<< orphan*/  channumber; int /*<<< orphan*/  radiotype; } ;
struct TYPE_5__ {TYPE_1__** channels; } ;
struct TYPE_4__ {int /*<<< orphan*/  hw_value; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_SCAN_RADIO_TYPE_BG ; 
 int LBS_DWELL_ACTIVE ; 
 int LBS_DWELL_PASSIVE ; 
 int TLV_TYPE_CHANLIST ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lbs_add_channel_list_tlv(struct lbs_private *priv, u8 *tlv,
				    int last_channel, int active_scan)
{
	int chanscanparamsize = sizeof(struct chanscanparamset) *
		(last_channel - priv->scan_channel);

	struct mrvl_ie_header *header = (void *) tlv;

	/*
	 * TLV-ID CHANLIST  01 01
	 * length           0e 00
	 * channel          00 01 00 00 00 64 00
	 *   radio type     00
	 *   channel           01
	 *   scan type            00
	 *   min scan time           00 00
	 *   max scan time                 64 00
	 * channel 2        00 02 00 00 00 64 00
	 *
	 */

	header->type = cpu_to_le16(TLV_TYPE_CHANLIST);
	header->len  = cpu_to_le16(chanscanparamsize);
	tlv += sizeof(struct mrvl_ie_header);

	/* lbs_deb_scan("scan: channels %d to %d\n", priv->scan_channel,
		     last_channel); */
	memset(tlv, 0, chanscanparamsize);

	while (priv->scan_channel < last_channel) {
		struct chanscanparamset *param = (void *) tlv;

		param->radiotype = CMD_SCAN_RADIO_TYPE_BG;
		param->channumber =
			priv->scan_req->channels[priv->scan_channel]->hw_value;
		if (active_scan) {
			param->maxscantime = cpu_to_le16(LBS_DWELL_ACTIVE);
		} else {
			param->chanscanmode.passivescan = 1;
			param->maxscantime = cpu_to_le16(LBS_DWELL_PASSIVE);
		}
		tlv += sizeof(struct chanscanparamset);
		priv->scan_channel++;
	}
	return sizeof(struct mrvl_ie_header) + chanscanparamsize;
}