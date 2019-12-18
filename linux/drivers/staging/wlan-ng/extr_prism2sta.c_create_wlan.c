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
struct wlandevice {int nsdcaps; int dot11_desired_bss_type; int /*<<< orphan*/  tx_timeout; int /*<<< orphan*/  set_multicast_list; int /*<<< orphan*/  mlmerequest; int /*<<< orphan*/  txframe; int /*<<< orphan*/  reset; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct wlandevice* priv; int /*<<< orphan*/  msdstate; int /*<<< orphan*/  nsdname; } ;
struct hfa384x {int nsdcaps; int dot11_desired_bss_type; int /*<<< orphan*/  tx_timeout; int /*<<< orphan*/  set_multicast_list; int /*<<< orphan*/  mlmerequest; int /*<<< orphan*/  txframe; int /*<<< orphan*/  reset; int /*<<< orphan*/  close; int /*<<< orphan*/  open; struct hfa384x* priv; int /*<<< orphan*/  msdstate; int /*<<< orphan*/  nsdname; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int P80211_NSDCAP_AUTOJOIN ; 
 int P80211_NSDCAP_HWFRAGMENT ; 
 int /*<<< orphan*/  WLAN_MSD_HWPRESENT_PENDING ; 
 int /*<<< orphan*/  dev_info ; 
 int /*<<< orphan*/  hfa384x_tx_timeout ; 
 int /*<<< orphan*/  kfree (struct wlandevice*) ; 
 struct wlandevice* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prism2sta_close ; 
 int /*<<< orphan*/  prism2sta_mlmerequest ; 
 int /*<<< orphan*/  prism2sta_open ; 
 int /*<<< orphan*/  prism2sta_reset ; 
 int /*<<< orphan*/  prism2sta_setmulticast ; 
 int /*<<< orphan*/  prism2sta_txframe ; 

__attribute__((used)) static struct wlandevice *create_wlan(void)
{
	struct wlandevice *wlandev = NULL;
	struct hfa384x *hw = NULL;

	/* Alloc our structures */
	wlandev = kzalloc(sizeof(*wlandev), GFP_KERNEL);
	hw = kzalloc(sizeof(*hw), GFP_KERNEL);

	if (!wlandev || !hw) {
		kfree(wlandev);
		kfree(hw);
		return NULL;
	}

	/* Initialize the network device object. */
	wlandev->nsdname = dev_info;
	wlandev->msdstate = WLAN_MSD_HWPRESENT_PENDING;
	wlandev->priv = hw;
	wlandev->open = prism2sta_open;
	wlandev->close = prism2sta_close;
	wlandev->reset = prism2sta_reset;
	wlandev->txframe = prism2sta_txframe;
	wlandev->mlmerequest = prism2sta_mlmerequest;
	wlandev->set_multicast_list = prism2sta_setmulticast;
	wlandev->tx_timeout = hfa384x_tx_timeout;

	wlandev->nsdcaps = P80211_NSDCAP_HWFRAGMENT | P80211_NSDCAP_AUTOJOIN;

	/* Initialize the device private data structure. */
	hw->dot11_desired_bss_type = 1;

	return wlandev;
}