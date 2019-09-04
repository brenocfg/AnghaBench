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
struct em28xx_led {int inverted; int gpio_mask; int /*<<< orphan*/  gpio_reg; } ;
struct em28xx {scalar_t__ chip_id; scalar_t__ ts; int dvb_max_pkt_size_isoc; scalar_t__ mode; scalar_t__ is_webcam; scalar_t__ dvb_xfer_bulk; } ;

/* Variables and functions */
 scalar_t__ CHIP_ID_EM28174 ; 
 scalar_t__ CHIP_ID_EM28178 ; 
 scalar_t__ CHIP_ID_EM2874 ; 
 scalar_t__ CHIP_ID_EM2884 ; 
 int EM2874_R5D_TS1_PKT_SIZE ; 
 int EM2874_R5E_TS2_PKT_SIZE ; 
 int /*<<< orphan*/  EM2874_R5F_TS_ENABLE ; 
 int EM2874_TS1_CAPTURE_ENABLE ; 
 int EM2874_TS1_FILTER_ENABLE ; 
 int EM2874_TS1_NULL_DISCARD ; 
 int EM2874_TS2_CAPTURE_ENABLE ; 
 int EM2874_TS2_FILTER_ENABLE ; 
 int EM2874_TS2_NULL_DISCARD ; 
 scalar_t__ EM28XX_ANALOG_MODE ; 
 int /*<<< orphan*/  EM28XX_LED_ANALOG_CAPTURING ; 
 int /*<<< orphan*/  EM28XX_LED_DIGITAL_CAPTURING ; 
 int /*<<< orphan*/  EM28XX_R0C_USBSUSP ; 
 int EM28XX_R12_VINENABLE ; 
 scalar_t__ PRIMARY_TS ; 
 struct em28xx_led* em28xx_find_led (struct em28xx*,int /*<<< orphan*/ ) ; 
 int em28xx_write_reg (struct em28xx*,int,int) ; 
 int em28xx_write_reg_bits (struct em28xx*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

int em28xx_capture_start(struct em28xx *dev, int start)
{
	int rc;
	const struct em28xx_led *led = NULL;

	if (dev->chip_id == CHIP_ID_EM2874 ||
	    dev->chip_id == CHIP_ID_EM2884 ||
	    dev->chip_id == CHIP_ID_EM28174 ||
	    dev->chip_id == CHIP_ID_EM28178) {
		/* The Transport Stream Enable Register moved in em2874 */
		if (dev->dvb_xfer_bulk) {
			/* Max Tx Size = 188 * 256 = 48128 - LCM(188,512) * 2 */
			em28xx_write_reg(dev, (dev->ts == PRIMARY_TS) ?
					 EM2874_R5D_TS1_PKT_SIZE :
					 EM2874_R5E_TS2_PKT_SIZE,
					 0xff);
		} else {
			/* ISOC Maximum Transfer Size = 188 * 5 */
			em28xx_write_reg(dev, (dev->ts == PRIMARY_TS) ?
					 EM2874_R5D_TS1_PKT_SIZE :
					 EM2874_R5E_TS2_PKT_SIZE,
					 dev->dvb_max_pkt_size_isoc / 188);
		}
		if (dev->ts == PRIMARY_TS)
			rc = em28xx_write_reg_bits(dev,
						   EM2874_R5F_TS_ENABLE,
						   start ? EM2874_TS1_CAPTURE_ENABLE : 0x00,
						   EM2874_TS1_CAPTURE_ENABLE | EM2874_TS1_FILTER_ENABLE | EM2874_TS1_NULL_DISCARD);
		else
			rc = em28xx_write_reg_bits(dev,
						   EM2874_R5F_TS_ENABLE,
						   start ? EM2874_TS2_CAPTURE_ENABLE : 0x00,
						   EM2874_TS2_CAPTURE_ENABLE | EM2874_TS2_FILTER_ENABLE | EM2874_TS2_NULL_DISCARD);
	} else {
		/* FIXME: which is the best order? */
		/* video registers are sampled by VREF */
		rc = em28xx_write_reg_bits(dev, EM28XX_R0C_USBSUSP,
					   start ? 0x10 : 0x00, 0x10);
		if (rc < 0)
			return rc;

		if (start) {
			if (dev->is_webcam)
				rc = em28xx_write_reg(dev, 0x13, 0x0c);

			/* Enable video capture */
			rc = em28xx_write_reg(dev, 0x48, 0x00);
			if (rc < 0)
				return rc;

			if (dev->mode == EM28XX_ANALOG_MODE)
				rc = em28xx_write_reg(dev,
						      EM28XX_R12_VINENABLE,
						      0x67);
			else
				rc = em28xx_write_reg(dev,
						      EM28XX_R12_VINENABLE,
						      0x37);
			if (rc < 0)
				return rc;

			usleep_range(10000, 11000);
		} else {
			/* disable video capture */
			rc = em28xx_write_reg(dev, EM28XX_R12_VINENABLE, 0x27);
		}
	}

	if (dev->mode == EM28XX_ANALOG_MODE)
		led = em28xx_find_led(dev, EM28XX_LED_ANALOG_CAPTURING);
	else
		led = em28xx_find_led(dev, EM28XX_LED_DIGITAL_CAPTURING);

	if (led)
		em28xx_write_reg_bits(dev, led->gpio_reg,
				      (!start ^ led->inverted) ?
				      ~led->gpio_mask : led->gpio_mask,
				      led->gpio_mask);

	return rc;
}