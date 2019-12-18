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
typedef  int /*<<< orphan*/  u8 ;
struct wmi_tx_pwr_reply {int /*<<< orphan*/  dbM; } ;
struct wmi {int /*<<< orphan*/  parent_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  ath6kl_txpwr_rx_evt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath6kl_wmi_tx_pwr_reply_rx(struct wmi *wmi, u8 *datap, int len)
{
	struct wmi_tx_pwr_reply *reply;

	if (len < sizeof(struct wmi_tx_pwr_reply))
		return -EINVAL;

	reply = (struct wmi_tx_pwr_reply *) datap;
	ath6kl_txpwr_rx_evt(wmi->parent_dev, reply->dbM);

	return 0;
}