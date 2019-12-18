#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct il_spectrum_cmd {int flags; TYPE_3__* channels; scalar_t__ start_time; void* len; int /*<<< orphan*/  filter_flags; void* channel_count; } ;
struct TYPE_13__ {int id; int /*<<< orphan*/  status; } ;
struct TYPE_14__ {TYPE_6__ spectrum; } ;
struct TYPE_12__ {int flags; } ;
struct il_rx_pkt {TYPE_7__ u; TYPE_5__ hdr; } ;
struct TYPE_11__ {int flags; } ;
struct TYPE_9__ {int /*<<< orphan*/  beacon_interval; } ;
struct TYPE_8__ {int /*<<< orphan*/  last_beacon_time; scalar_t__ last_tsf; } ;
struct il_priv {int /*<<< orphan*/  measurement_status; TYPE_4__ active; TYPE_2__ timing; TYPE_1__ _3945; } ;
struct il_host_cmd {void* data; int len; scalar_t__ reply_page; int /*<<< orphan*/  flags; int /*<<< orphan*/  id; } ;
struct ieee80211_measurement_params {int /*<<< orphan*/  channel; int /*<<< orphan*/  start_time; int /*<<< orphan*/  duration; } ;
typedef  int /*<<< orphan*/  spectrum ;
struct TYPE_10__ {int /*<<< orphan*/  type; int /*<<< orphan*/  channel; int /*<<< orphan*/  duration; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_WANT_SKB ; 
 int /*<<< orphan*/  C_SPECTRUM_MEASUREMENT ; 
 int /*<<< orphan*/  D_INFO (char*,int) ; 
 int EAGAIN ; 
 int EIO ; 
 int IL_CMD_FAILED_MSK ; 
 int /*<<< orphan*/  IL_ERR (char*) ; 
 int /*<<< orphan*/  MEASUREMENT_ACTIVE ; 
 int /*<<< orphan*/  MEASUREMENT_FILTER_FLAG ; 
 int /*<<< orphan*/  MEASUREMENT_READY ; 
 int RXON_FLG_ANT_A_MSK ; 
 int RXON_FLG_AUTO_DETECT_MSK ; 
 int RXON_FLG_BAND_24G_MSK ; 
 int RXON_FLG_DIS_DIV_MSK ; 
 int RXON_FLG_TGG_PROTECT_MSK ; 
 int RXON_FLG_TSF2HOST_MSK ; 
 int TIME_UNIT ; 
 void* cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 scalar_t__ il_add_beacon_time (struct il_priv*,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  il_free_pages (struct il_priv*,scalar_t__) ; 
 scalar_t__ il_is_associated (struct il_priv*) ; 
 int il_send_cmd_sync (struct il_priv*,struct il_host_cmd*) ; 
 scalar_t__ il_usecs_to_beacons (struct il_priv*,scalar_t__,int) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct il_spectrum_cmd*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
il3945_get_measurement(struct il_priv *il,
		       struct ieee80211_measurement_params *params, u8 type)
{
	struct il_spectrum_cmd spectrum;
	struct il_rx_pkt *pkt;
	struct il_host_cmd cmd = {
		.id = C_SPECTRUM_MEASUREMENT,
		.data = (void *)&spectrum,
		.flags = CMD_WANT_SKB,
	};
	u32 add_time = le64_to_cpu(params->start_time);
	int rc;
	int spectrum_resp_status;
	int duration = le16_to_cpu(params->duration);

	if (il_is_associated(il))
		add_time =
		    il_usecs_to_beacons(il,
					le64_to_cpu(params->start_time) -
					il->_3945.last_tsf,
					le16_to_cpu(il->timing.beacon_interval));

	memset(&spectrum, 0, sizeof(spectrum));

	spectrum.channel_count = cpu_to_le16(1);
	spectrum.flags =
	    RXON_FLG_TSF2HOST_MSK | RXON_FLG_ANT_A_MSK | RXON_FLG_DIS_DIV_MSK;
	spectrum.filter_flags = MEASUREMENT_FILTER_FLAG;
	cmd.len = sizeof(spectrum);
	spectrum.len = cpu_to_le16(cmd.len - sizeof(spectrum.len));

	if (il_is_associated(il))
		spectrum.start_time =
		    il_add_beacon_time(il, il->_3945.last_beacon_time, add_time,
				       le16_to_cpu(il->timing.beacon_interval));
	else
		spectrum.start_time = 0;

	spectrum.channels[0].duration = cpu_to_le32(duration * TIME_UNIT);
	spectrum.channels[0].channel = params->channel;
	spectrum.channels[0].type = type;
	if (il->active.flags & RXON_FLG_BAND_24G_MSK)
		spectrum.flags |=
		    RXON_FLG_BAND_24G_MSK | RXON_FLG_AUTO_DETECT_MSK |
		    RXON_FLG_TGG_PROTECT_MSK;

	rc = il_send_cmd_sync(il, &cmd);
	if (rc)
		return rc;

	pkt = (struct il_rx_pkt *)cmd.reply_page;
	if (pkt->hdr.flags & IL_CMD_FAILED_MSK) {
		IL_ERR("Bad return from N_RX_ON_ASSOC command\n");
		rc = -EIO;
	}

	spectrum_resp_status = le16_to_cpu(pkt->u.spectrum.status);
	switch (spectrum_resp_status) {
	case 0:		/* Command will be handled */
		if (pkt->u.spectrum.id != 0xff) {
			D_INFO("Replaced existing measurement: %d\n",
			       pkt->u.spectrum.id);
			il->measurement_status &= ~MEASUREMENT_READY;
		}
		il->measurement_status |= MEASUREMENT_ACTIVE;
		rc = 0;
		break;

	case 1:		/* Command will not be handled */
		rc = -EAGAIN;
		break;
	}

	il_free_pages(il, cmd.reply_page);

	return rc;
}