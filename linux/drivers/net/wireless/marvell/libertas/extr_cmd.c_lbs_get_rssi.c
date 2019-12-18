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
struct lbs_private {int dummy; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_rssi {void* nf; void* n_or_snr; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  s8 ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAL_NF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CAL_RSSI (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_802_11_RSSI ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_rssi*) ; 
 int /*<<< orphan*/  le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_rssi*,int /*<<< orphan*/ ,int) ; 

int lbs_get_rssi(struct lbs_private *priv, s8 *rssi, s8 *nf)
{
	struct cmd_ds_802_11_rssi cmd;
	int ret = 0;

	BUG_ON(rssi == NULL);
	BUG_ON(nf == NULL);

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	/* Average SNR over last 8 beacons */
	cmd.n_or_snr = cpu_to_le16(8);

	ret = lbs_cmd_with_response(priv, CMD_802_11_RSSI, &cmd);
	if (ret == 0) {
		*nf = CAL_NF(le16_to_cpu(cmd.nf));
		*rssi = CAL_RSSI(le16_to_cpu(cmd.n_or_snr), le16_to_cpu(cmd.nf));
	}

	return ret;
}