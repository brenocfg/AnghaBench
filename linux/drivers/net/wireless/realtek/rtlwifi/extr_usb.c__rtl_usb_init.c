#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct usb_interface {TYPE_3__* cur_altsetting; } ;
struct usb_endpoint_descriptor {int /*<<< orphan*/  bInterval; int /*<<< orphan*/  wMaxPacketSize; int /*<<< orphan*/  bEndpointAddress; } ;
struct rtl_usb_priv {int dummy; } ;
struct rtl_usb {scalar_t__ out_ep_nums; scalar_t__ in_ep_nums; int /*<<< orphan*/  usb_mq_to_hwq; struct usb_interface* intf; } ;
struct rtl_priv {TYPE_5__* cfg; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_10__ {TYPE_4__* usb_interface_cfg; } ;
struct TYPE_9__ {scalar_t__ in_ep_num; int (* usb_endpoint_mapping ) (struct ieee80211_hw*) ;int /*<<< orphan*/  usb_mq_to_hwq; } ;
struct TYPE_6__ {size_t bNumEndpoints; } ;
struct TYPE_8__ {TYPE_2__* endpoint; TYPE_1__ desc; } ;
struct TYPE_7__ {struct usb_endpoint_descriptor desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMP_INIT ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int EINVAL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _rtl_usb_init_rx (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl_usb_init_tx (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 struct rtl_usb* rtl_usbdev (struct rtl_usb_priv*) ; 
 struct rtl_usb_priv* rtl_usbpriv (struct ieee80211_hw*) ; 
 int stub1 (struct ieee80211_hw*) ; 
 scalar_t__ usb_endpoint_dir_in (struct usb_endpoint_descriptor*) ; 
 scalar_t__ usb_endpoint_dir_out (struct usb_endpoint_descriptor*) ; 

__attribute__((used)) static int _rtl_usb_init(struct ieee80211_hw *hw)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_usb_priv *usb_priv = rtl_usbpriv(hw);
	struct rtl_usb *rtlusb = rtl_usbdev(usb_priv);
	int err;
	u8 epidx;
	struct usb_interface	*usb_intf = rtlusb->intf;
	u8 epnums = usb_intf->cur_altsetting->desc.bNumEndpoints;

	rtlusb->out_ep_nums = rtlusb->in_ep_nums = 0;
	for (epidx = 0; epidx < epnums; epidx++) {
		struct usb_endpoint_descriptor *pep_desc;

		pep_desc = &usb_intf->cur_altsetting->endpoint[epidx].desc;

		if (usb_endpoint_dir_in(pep_desc))
			rtlusb->in_ep_nums++;
		else if (usb_endpoint_dir_out(pep_desc))
			rtlusb->out_ep_nums++;

		RT_TRACE(rtlpriv, COMP_INIT, DBG_DMESG,
			 "USB EP(0x%02x), MaxPacketSize=%d, Interval=%d\n",
			 pep_desc->bEndpointAddress, pep_desc->wMaxPacketSize,
			 pep_desc->bInterval);
	}
	if (rtlusb->in_ep_nums <  rtlpriv->cfg->usb_interface_cfg->in_ep_num) {
		pr_err("Too few input end points found\n");
		return -EINVAL;
	}
	if (rtlusb->out_ep_nums == 0) {
		pr_err("No output end points found\n");
		return -EINVAL;
	}
	/* usb endpoint mapping */
	err = rtlpriv->cfg->usb_interface_cfg->usb_endpoint_mapping(hw);
	rtlusb->usb_mq_to_hwq =  rtlpriv->cfg->usb_interface_cfg->usb_mq_to_hwq;
	_rtl_usb_init_tx(hw);
	_rtl_usb_init_rx(hw);
	return err;
}