#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int id; int variant; int major; int minor; int role; int bottom; int top; } ;
typedef  TYPE_1__ u8 ;
typedef  int u16 ;
struct wlandevice {TYPE_2__* netdev; int /*<<< orphan*/  nsdcaps; struct hfa384x* priv; } ;
struct hfa384x_compident {int dummy; } ;
struct hfa384x_caplevel {int dummy; } ;
struct hfa384x {int mm_mods; int dbmadjust; TYPE_1__ ident_sta_fw; TYPE_1__ cap_act_sta_mfi; TYPE_1__ cap_act_sta_cfi; TYPE_1__ cap_act_pri_cfi; TYPE_1__ cap_sup_sta; TYPE_1__ cap_sup_pri; TYPE_1__ cap_sup_cfi; TYPE_1__ cap_sup_mfi; TYPE_1__ ident_nic; TYPE_1__ ident_pri_fw; } ;
struct TYPE_6__ {TYPE_1__* dev_addr; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int GENMASK (int,int) ; 
 scalar_t__ HFA384x_FIRMWARE_VERSION (int,int,int) ; 
 int /*<<< orphan*/  HFA384x_RID_CFISUPRANGE ; 
 int /*<<< orphan*/  HFA384x_RID_CNFDBMADJUST ; 
 int /*<<< orphan*/  HFA384x_RID_CNFOWNMACADDR ; 
 int /*<<< orphan*/  HFA384x_RID_MFISUPRANGE ; 
 int /*<<< orphan*/  HFA384x_RID_NICIDENTITY ; 
 int /*<<< orphan*/  HFA384x_RID_NICSERIALNUMBER ; 
 int HFA384x_RID_NICSERIALNUMBER_LEN ; 
 int /*<<< orphan*/  HFA384x_RID_PRIIDENTITY ; 
 int /*<<< orphan*/  HFA384x_RID_PRISUPRANGE ; 
 int /*<<< orphan*/  HFA384x_RID_PRIVACYOPTIMP ; 
 int /*<<< orphan*/  HFA384x_RID_PRI_CFIACTRANGES ; 
 int /*<<< orphan*/  HFA384x_RID_STAIDENTITY ; 
 int /*<<< orphan*/  HFA384x_RID_STASUPRANGE ; 
 int /*<<< orphan*/  HFA384x_RID_STA_CFIACTRANGES ; 
 int /*<<< orphan*/  HFA384x_RID_STA_MFIACTRANGES ; 
 int /*<<< orphan*/  P80211_NSDCAP_HARDWAREWEP ; 
 int /*<<< orphan*/  P80211_NSDCAP_NOSCAN ; 
 int /*<<< orphan*/  P80211_NSDCAP_SHORT_PREAMBLE ; 
 int hfa384x_drvr_getconfig (struct hfa384x*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  hfa384x_drvr_getconfig16 (struct hfa384x*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  le16_to_cpus (int*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  netdev_info (TYPE_2__*,char*,int,...) ; 

__attribute__((used)) static int prism2sta_getcardinfo(struct wlandevice *wlandev)
{
	int result = 0;
	struct hfa384x *hw = wlandev->priv;
	u16 temp;
	u8 snum[HFA384x_RID_NICSERIALNUMBER_LEN];

	/* Collect version and compatibility info */
	/*  Some are critical, some are not */
	/* NIC identity */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_NICIDENTITY,
					&hw->ident_nic,
					sizeof(struct hfa384x_compident));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve NICIDENTITY\n");
		goto failed;
	}

	/* get all the nic id fields in host byte order */
	le16_to_cpus(&hw->ident_nic.id);
	le16_to_cpus(&hw->ident_nic.variant);
	le16_to_cpus(&hw->ident_nic.major);
	le16_to_cpus(&hw->ident_nic.minor);

	netdev_info(wlandev->netdev, "ident: nic h/w: id=0x%02x %d.%d.%d\n",
		    hw->ident_nic.id, hw->ident_nic.major,
		    hw->ident_nic.minor, hw->ident_nic.variant);

	/* Primary f/w identity */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_PRIIDENTITY,
					&hw->ident_pri_fw,
					sizeof(struct hfa384x_compident));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve PRIIDENTITY\n");
		goto failed;
	}

	/* get all the private fw id fields in host byte order */
	le16_to_cpus(&hw->ident_pri_fw.id);
	le16_to_cpus(&hw->ident_pri_fw.variant);
	le16_to_cpus(&hw->ident_pri_fw.major);
	le16_to_cpus(&hw->ident_pri_fw.minor);

	netdev_info(wlandev->netdev, "ident: pri f/w: id=0x%02x %d.%d.%d\n",
		    hw->ident_pri_fw.id, hw->ident_pri_fw.major,
		    hw->ident_pri_fw.minor, hw->ident_pri_fw.variant);

	/* Station (Secondary?) f/w identity */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_STAIDENTITY,
					&hw->ident_sta_fw,
					sizeof(struct hfa384x_compident));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve STAIDENTITY\n");
		goto failed;
	}

	if (hw->ident_nic.id < 0x8000) {
		netdev_err(wlandev->netdev,
			   "FATAL: Card is not an Intersil Prism2/2.5/3\n");
		result = -1;
		goto failed;
	}

	/* get all the station fw id fields in host byte order */
	le16_to_cpus(&hw->ident_sta_fw.id);
	le16_to_cpus(&hw->ident_sta_fw.variant);
	le16_to_cpus(&hw->ident_sta_fw.major);
	le16_to_cpus(&hw->ident_sta_fw.minor);

	/* strip out the 'special' variant bits */
	hw->mm_mods = hw->ident_sta_fw.variant & GENMASK(15, 14);
	hw->ident_sta_fw.variant &= ~((u16)GENMASK(15, 14));

	if (hw->ident_sta_fw.id == 0x1f) {
		netdev_info(wlandev->netdev,
			    "ident: sta f/w: id=0x%02x %d.%d.%d\n",
			    hw->ident_sta_fw.id, hw->ident_sta_fw.major,
			    hw->ident_sta_fw.minor, hw->ident_sta_fw.variant);
	} else {
		netdev_info(wlandev->netdev,
			    "ident:  ap f/w: id=0x%02x %d.%d.%d\n",
			    hw->ident_sta_fw.id, hw->ident_sta_fw.major,
			    hw->ident_sta_fw.minor, hw->ident_sta_fw.variant);
		netdev_err(wlandev->netdev, "Unsupported Tertiary AP firmware loaded!\n");
		goto failed;
	}

	/* Compatibility range, Modem supplier */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_MFISUPRANGE,
					&hw->cap_sup_mfi,
					sizeof(struct hfa384x_caplevel));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve MFISUPRANGE\n");
		goto failed;
	}

	/* get all the Compatibility range, modem interface supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_sup_mfi.role);
	le16_to_cpus(&hw->cap_sup_mfi.id);
	le16_to_cpus(&hw->cap_sup_mfi.variant);
	le16_to_cpus(&hw->cap_sup_mfi.bottom);
	le16_to_cpus(&hw->cap_sup_mfi.top);

	netdev_info(wlandev->netdev,
		    "MFI:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_sup_mfi.role, hw->cap_sup_mfi.id,
		    hw->cap_sup_mfi.variant, hw->cap_sup_mfi.bottom,
		    hw->cap_sup_mfi.top);

	/* Compatibility range, Controller supplier */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_CFISUPRANGE,
					&hw->cap_sup_cfi,
					sizeof(struct hfa384x_caplevel));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve CFISUPRANGE\n");
		goto failed;
	}

	/* get all the Compatibility range, controller interface supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_sup_cfi.role);
	le16_to_cpus(&hw->cap_sup_cfi.id);
	le16_to_cpus(&hw->cap_sup_cfi.variant);
	le16_to_cpus(&hw->cap_sup_cfi.bottom);
	le16_to_cpus(&hw->cap_sup_cfi.top);

	netdev_info(wlandev->netdev,
		    "CFI:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_sup_cfi.role, hw->cap_sup_cfi.id,
		    hw->cap_sup_cfi.variant, hw->cap_sup_cfi.bottom,
		    hw->cap_sup_cfi.top);

	/* Compatibility range, Primary f/w supplier */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_PRISUPRANGE,
					&hw->cap_sup_pri,
					sizeof(struct hfa384x_caplevel));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve PRISUPRANGE\n");
		goto failed;
	}

	/* get all the Compatibility range, primary firmware supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_sup_pri.role);
	le16_to_cpus(&hw->cap_sup_pri.id);
	le16_to_cpus(&hw->cap_sup_pri.variant);
	le16_to_cpus(&hw->cap_sup_pri.bottom);
	le16_to_cpus(&hw->cap_sup_pri.top);

	netdev_info(wlandev->netdev,
		    "PRI:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_sup_pri.role, hw->cap_sup_pri.id,
		    hw->cap_sup_pri.variant, hw->cap_sup_pri.bottom,
		    hw->cap_sup_pri.top);

	/* Compatibility range, Station f/w supplier */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_STASUPRANGE,
					&hw->cap_sup_sta,
					sizeof(struct hfa384x_caplevel));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve STASUPRANGE\n");
		goto failed;
	}

	/* get all the Compatibility range, station firmware supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_sup_sta.role);
	le16_to_cpus(&hw->cap_sup_sta.id);
	le16_to_cpus(&hw->cap_sup_sta.variant);
	le16_to_cpus(&hw->cap_sup_sta.bottom);
	le16_to_cpus(&hw->cap_sup_sta.top);

	if (hw->cap_sup_sta.id == 0x04) {
		netdev_info(wlandev->netdev,
			    "STA:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
			    hw->cap_sup_sta.role, hw->cap_sup_sta.id,
			    hw->cap_sup_sta.variant, hw->cap_sup_sta.bottom,
			    hw->cap_sup_sta.top);
	} else {
		netdev_info(wlandev->netdev,
			    "AP:SUP:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
			    hw->cap_sup_sta.role, hw->cap_sup_sta.id,
			    hw->cap_sup_sta.variant, hw->cap_sup_sta.bottom,
			    hw->cap_sup_sta.top);
	}

	/* Compatibility range, primary f/w actor, CFI supplier */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_PRI_CFIACTRANGES,
					&hw->cap_act_pri_cfi,
					sizeof(struct hfa384x_caplevel));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve PRI_CFIACTRANGES\n");
		goto failed;
	}

	/* get all the Compatibility range, primary f/w actor, CFI supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_act_pri_cfi.role);
	le16_to_cpus(&hw->cap_act_pri_cfi.id);
	le16_to_cpus(&hw->cap_act_pri_cfi.variant);
	le16_to_cpus(&hw->cap_act_pri_cfi.bottom);
	le16_to_cpus(&hw->cap_act_pri_cfi.top);

	netdev_info(wlandev->netdev,
		    "PRI-CFI:ACT:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_act_pri_cfi.role, hw->cap_act_pri_cfi.id,
		    hw->cap_act_pri_cfi.variant, hw->cap_act_pri_cfi.bottom,
		    hw->cap_act_pri_cfi.top);

	/* Compatibility range, sta f/w actor, CFI supplier */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_STA_CFIACTRANGES,
					&hw->cap_act_sta_cfi,
					sizeof(struct hfa384x_caplevel));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve STA_CFIACTRANGES\n");
		goto failed;
	}

	/* get all the Compatibility range, station f/w actor, CFI supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_act_sta_cfi.role);
	le16_to_cpus(&hw->cap_act_sta_cfi.id);
	le16_to_cpus(&hw->cap_act_sta_cfi.variant);
	le16_to_cpus(&hw->cap_act_sta_cfi.bottom);
	le16_to_cpus(&hw->cap_act_sta_cfi.top);

	netdev_info(wlandev->netdev,
		    "STA-CFI:ACT:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_act_sta_cfi.role, hw->cap_act_sta_cfi.id,
		    hw->cap_act_sta_cfi.variant, hw->cap_act_sta_cfi.bottom,
		    hw->cap_act_sta_cfi.top);

	/* Compatibility range, sta f/w actor, MFI supplier */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_STA_MFIACTRANGES,
					&hw->cap_act_sta_mfi,
					sizeof(struct hfa384x_caplevel));
	if (result) {
		netdev_err(wlandev->netdev, "Failed to retrieve STA_MFIACTRANGES\n");
		goto failed;
	}

	/* get all the Compatibility range, station f/w actor, MFI supplier
	 * fields in byte order
	 */
	le16_to_cpus(&hw->cap_act_sta_mfi.role);
	le16_to_cpus(&hw->cap_act_sta_mfi.id);
	le16_to_cpus(&hw->cap_act_sta_mfi.variant);
	le16_to_cpus(&hw->cap_act_sta_mfi.bottom);
	le16_to_cpus(&hw->cap_act_sta_mfi.top);

	netdev_info(wlandev->netdev,
		    "STA-MFI:ACT:role=0x%02x:id=0x%02x:var=0x%02x:b/t=%d/%d\n",
		    hw->cap_act_sta_mfi.role, hw->cap_act_sta_mfi.id,
		    hw->cap_act_sta_mfi.variant, hw->cap_act_sta_mfi.bottom,
		    hw->cap_act_sta_mfi.top);

	/* Serial Number */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_NICSERIALNUMBER,
					snum, HFA384x_RID_NICSERIALNUMBER_LEN);
	if (!result) {
		netdev_info(wlandev->netdev, "Prism2 card SN: %*pE\n",
			    HFA384x_RID_NICSERIALNUMBER_LEN, snum);
	} else {
		netdev_err(wlandev->netdev, "Failed to retrieve Prism2 Card SN\n");
		goto failed;
	}

	/* Collect the MAC address */
	result = hfa384x_drvr_getconfig(hw, HFA384x_RID_CNFOWNMACADDR,
					wlandev->netdev->dev_addr, ETH_ALEN);
	if (result != 0) {
		netdev_err(wlandev->netdev, "Failed to retrieve mac address\n");
		goto failed;
	}

	/* short preamble is always implemented */
	wlandev->nsdcaps |= P80211_NSDCAP_SHORT_PREAMBLE;

	/* find out if hardware wep is implemented */
	hfa384x_drvr_getconfig16(hw, HFA384x_RID_PRIVACYOPTIMP, &temp);
	if (temp)
		wlandev->nsdcaps |= P80211_NSDCAP_HARDWAREWEP;

	/* get the dBm Scaling constant */
	hfa384x_drvr_getconfig16(hw, HFA384x_RID_CNFDBMADJUST, &temp);
	hw->dbmadjust = temp;

	/* Only enable scan by default on newer firmware */
	if (HFA384x_FIRMWARE_VERSION(hw->ident_sta_fw.major,
				     hw->ident_sta_fw.minor,
				     hw->ident_sta_fw.variant) <
	    HFA384x_FIRMWARE_VERSION(1, 5, 5)) {
		wlandev->nsdcaps |= P80211_NSDCAP_NOSCAN;
	}

	/* TODO: Set any internally managed config items */

	goto done;
failed:
	netdev_err(wlandev->netdev, "Failed, result=%d\n", result);
done:
	return result;
}