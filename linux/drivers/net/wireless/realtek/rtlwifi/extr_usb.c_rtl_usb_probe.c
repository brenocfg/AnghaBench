#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct usb_device_id {int dummy; } ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct TYPE_9__ {struct usb_device* udev; struct usb_interface* intf; } ;
struct rtl_usb_priv {TYPE_3__ dev; } ;
struct TYPE_12__ {int mac80211_registered; } ;
struct TYPE_10__ {int /*<<< orphan*/  interface; } ;
struct TYPE_8__ {int /*<<< orphan*/  lps_change_work; int /*<<< orphan*/  fill_h2c_cmd; } ;
struct TYPE_7__ {int /*<<< orphan*/  usb_lock; } ;
struct rtl_priv {int /*<<< orphan*/  firmware_loading_complete; int /*<<< orphan*/  status; TYPE_6__ mac80211; struct rtl_hal_cfg* cfg; int /*<<< orphan*/ * intf_ops; TYPE_4__ rtlhal; scalar_t__ usb_data_index; TYPE_2__ works; TYPE_1__ locks; int /*<<< orphan*/  usb_data; struct ieee80211_hw* hw; } ;
struct rtl_hal_cfg {TYPE_5__* ops; } ;
struct ieee80211_hw {struct rtl_priv* priv; } ;
struct TYPE_11__ {int /*<<< orphan*/  (* init_sw_leds ) (struct ieee80211_hw*) ;scalar_t__ (* init_sw_vars ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* read_eeprom_info ) (struct ieee80211_hw*) ;int /*<<< orphan*/  (* read_chip_version ) (struct ieee80211_hw*) ;} ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTF_USB ; 
 int /*<<< orphan*/  RTL_STATUS_INTERFACE_START ; 
 int /*<<< orphan*/  RTL_USB_MAX_RX_COUNT ; 
 int /*<<< orphan*/  SET_IEEE80211_DEV (struct ieee80211_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*) ; 
 int _rtl_usb_init (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl_usb_io_handler_init (int /*<<< orphan*/ *,struct ieee80211_hw*) ; 
 int /*<<< orphan*/  _rtl_usb_io_handler_release (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct ieee80211_hw* ieee80211_alloc_hw (int,int /*<<< orphan*/ *) ; 
 int ieee80211_register_hw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 struct usb_device* interface_to_usbdev (struct usb_interface*) ; 
 int /*<<< orphan*/  kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rtl_usb_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  rtl_deinit_core (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_fill_h2c_cmd_work_callback ; 
 int rtl_init_core (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_lps_change_work_callback ; 
 int /*<<< orphan*/  rtl_ops ; 
 int /*<<< orphan*/  rtl_usb_init_sw (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  rtl_usb_ops ; 
 struct rtl_usb_priv* rtl_usbpriv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ieee80211_hw*) ; 
 scalar_t__ stub3 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub4 (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  usb_get_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_put_dev (struct usb_device*) ; 
 int /*<<< orphan*/  usb_set_intfdata (struct usb_interface*,struct ieee80211_hw*) ; 

int rtl_usb_probe(struct usb_interface *intf,
		  const struct usb_device_id *id,
		  struct rtl_hal_cfg *rtl_hal_cfg)
{
	int err;
	struct ieee80211_hw *hw = NULL;
	struct rtl_priv *rtlpriv = NULL;
	struct usb_device	*udev;
	struct rtl_usb_priv *usb_priv;

	hw = ieee80211_alloc_hw(sizeof(struct rtl_priv) +
				sizeof(struct rtl_usb_priv), &rtl_ops);
	if (!hw) {
		WARN_ONCE(true, "rtl_usb: ieee80211 alloc failed\n");
		return -ENOMEM;
	}
	rtlpriv = hw->priv;
	rtlpriv->hw = hw;
	rtlpriv->usb_data = kcalloc(RTL_USB_MAX_RX_COUNT, sizeof(u32),
				    GFP_KERNEL);
	if (!rtlpriv->usb_data)
		return -ENOMEM;

	/* this spin lock must be initialized early */
	spin_lock_init(&rtlpriv->locks.usb_lock);
	INIT_WORK(&rtlpriv->works.fill_h2c_cmd,
		  rtl_fill_h2c_cmd_work_callback);
	INIT_WORK(&rtlpriv->works.lps_change_work,
		  rtl_lps_change_work_callback);

	rtlpriv->usb_data_index = 0;
	init_completion(&rtlpriv->firmware_loading_complete);
	SET_IEEE80211_DEV(hw, &intf->dev);
	udev = interface_to_usbdev(intf);
	usb_get_dev(udev);
	usb_priv = rtl_usbpriv(hw);
	memset(usb_priv, 0, sizeof(*usb_priv));
	usb_priv->dev.intf = intf;
	usb_priv->dev.udev = udev;
	usb_set_intfdata(intf, hw);
	/* init cfg & intf_ops */
	rtlpriv->rtlhal.interface = INTF_USB;
	rtlpriv->cfg = rtl_hal_cfg;
	rtlpriv->intf_ops = &rtl_usb_ops;
	/* Init IO handler */
	_rtl_usb_io_handler_init(&udev->dev, hw);
	rtlpriv->cfg->ops->read_chip_version(hw);
	/*like read eeprom and so on */
	rtlpriv->cfg->ops->read_eeprom_info(hw);
	err = _rtl_usb_init(hw);
	if (err)
		goto error_out2;
	rtl_usb_init_sw(hw);
	/* Init mac80211 sw */
	err = rtl_init_core(hw);
	if (err) {
		pr_err("Can't allocate sw for mac80211\n");
		goto error_out2;
	}
	if (rtlpriv->cfg->ops->init_sw_vars(hw)) {
		pr_err("Can't init_sw_vars\n");
		goto error_out;
	}
	rtlpriv->cfg->ops->init_sw_leds(hw);

	err = ieee80211_register_hw(hw);
	if (err) {
		pr_err("Can't register mac80211 hw.\n");
		err = -ENODEV;
		goto error_out;
	}
	rtlpriv->mac80211.mac80211_registered = 1;

	set_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status);
	return 0;

error_out:
	rtl_deinit_core(hw);
error_out2:
	_rtl_usb_io_handler_release(hw);
	usb_put_dev(udev);
	complete(&rtlpriv->firmware_loading_complete);
	return -ENODEV;
}