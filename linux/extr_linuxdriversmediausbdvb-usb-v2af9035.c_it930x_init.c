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
typedef  int u8 ;
typedef  int u16 ;
struct usb_interface {int /*<<< orphan*/  dev; } ;
struct state {int dual_mode; } ;
struct reg_val_mask {int member_0; int member_1; int member_2; int /*<<< orphan*/  mask; int /*<<< orphan*/  val; int /*<<< orphan*/  reg; } ;
struct dvb_usb_device {TYPE_1__* udev; struct usb_interface* intf; } ;
struct TYPE_2__ {int /*<<< orphan*/  speed; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct reg_val_mask*) ; 
 int /*<<< orphan*/  USB_SPEED_FULL ; 
 int af9035_wr_reg_mask (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct state* d_to_priv (struct dvb_usb_device*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int,...) ; 

__attribute__((used)) static int it930x_init(struct dvb_usb_device *d)
{
	struct state *state = d_to_priv(d);
	struct usb_interface *intf = d->intf;
	int ret, i;
	u16 frame_size = (d->udev->speed == USB_SPEED_FULL ? 5 : 816) * 188 / 4;
	u8 packet_size = (d->udev->speed == USB_SPEED_FULL ? 64 : 512) / 4;
	struct reg_val_mask tab[] = {
		{ 0x00da1a, 0x00, 0x01 }, /* ignore_sync_byte */
		{ 0x00f41f, 0x04, 0x04 }, /* dvbt_inten */
		{ 0x00da10, 0x00, 0x01 }, /* mpeg_full_speed */
		{ 0x00f41a, 0x01, 0x01 }, /* dvbt_en */
		{ 0x00da1d, 0x01, 0x01 }, /* mp2_sw_rst, reset EP4 */
		{ 0x00dd11, 0x00, 0x20 }, /* ep4_tx_en, disable EP4 */
		{ 0x00dd13, 0x00, 0x20 }, /* ep4_tx_nak, disable EP4 NAK */
		{ 0x00dd11, 0x20, 0x20 }, /* ep4_tx_en, enable EP4 */
		{ 0x00dd11, 0x00, 0x40 }, /* ep5_tx_en, disable EP5 */
		{ 0x00dd13, 0x00, 0x40 }, /* ep5_tx_nak, disable EP5 NAK */
		{ 0x00dd11, state->dual_mode << 6, 0x40 }, /* enable EP5 */
		{ 0x00dd88, (frame_size >> 0) & 0xff, 0xff},
		{ 0x00dd89, (frame_size >> 8) & 0xff, 0xff},
		{ 0x00dd0c, packet_size, 0xff},
		{ 0x00dd8a, (frame_size >> 0) & 0xff, 0xff},
		{ 0x00dd8b, (frame_size >> 8) & 0xff, 0xff},
		{ 0x00dd0d, packet_size, 0xff },
		{ 0x00da1d, 0x00, 0x01 }, /* mp2_sw_rst, disable */
		{ 0x00d833, 0x01, 0xff }, /* slew rate ctrl: slew rate boosts */
		{ 0x00d830, 0x00, 0xff }, /* Bit 0 of output driving control */
		{ 0x00d831, 0x01, 0xff }, /* Bit 1 of output driving control */
		{ 0x00d832, 0x00, 0xff }, /* Bit 2 of output driving control */

		/* suspend gpio1 for TS-C */
		{ 0x00d8b0, 0x01, 0xff }, /* gpio1 */
		{ 0x00d8b1, 0x01, 0xff }, /* gpio1 */
		{ 0x00d8af, 0x00, 0xff }, /* gpio1 */

		/* suspend gpio7 for TS-D */
		{ 0x00d8c4, 0x01, 0xff }, /* gpio7 */
		{ 0x00d8c5, 0x01, 0xff }, /* gpio7 */
		{ 0x00d8c3, 0x00, 0xff }, /* gpio7 */

		/* suspend gpio13 for TS-B */
		{ 0x00d8dc, 0x01, 0xff }, /* gpio13 */
		{ 0x00d8dd, 0x01, 0xff }, /* gpio13 */
		{ 0x00d8db, 0x00, 0xff }, /* gpio13 */

		/* suspend gpio14 for TS-E */
		{ 0x00d8e4, 0x01, 0xff }, /* gpio14 */
		{ 0x00d8e5, 0x01, 0xff }, /* gpio14 */
		{ 0x00d8e3, 0x00, 0xff }, /* gpio14 */

		/* suspend gpio15 for TS-A */
		{ 0x00d8e8, 0x01, 0xff }, /* gpio15 */
		{ 0x00d8e9, 0x01, 0xff }, /* gpio15 */
		{ 0x00d8e7, 0x00, 0xff }, /* gpio15 */

		{ 0x00da58, 0x00, 0x01 }, /* ts_in_src, serial */
		{ 0x00da73, 0x01, 0xff }, /* ts0_aggre_mode */
		{ 0x00da78, 0x47, 0xff }, /* ts0_sync_byte */
		{ 0x00da4c, 0x01, 0xff }, /* ts0_en */
		{ 0x00da5a, 0x1f, 0xff }, /* ts_fail_ignore */
	};

	dev_dbg(&intf->dev, "USB speed=%d frame_size=%04x packet_size=%02x\n",
		d->udev->speed, frame_size, packet_size);

	/* init endpoints */
	for (i = 0; i < ARRAY_SIZE(tab); i++) {
		ret = af9035_wr_reg_mask(d, tab[i].reg,
				tab[i].val, tab[i].mask);

		if (ret < 0)
			goto err;
	}

	return 0;
err:
	dev_dbg(&intf->dev, "failed=%d\n", ret);

	return ret;
}