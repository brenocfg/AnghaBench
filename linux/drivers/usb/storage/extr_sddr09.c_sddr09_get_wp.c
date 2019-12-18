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
struct us_data {int dummy; } ;
struct sddr09_card_info {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 unsigned char LUNBITS ; 
 int /*<<< orphan*/  SDDR09_WP ; 
 int sddr09_read_status (struct us_data*,unsigned char*) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data*,char*,...) ; 

__attribute__((used)) static int
sddr09_get_wp(struct us_data *us, struct sddr09_card_info *info) {
	int result;
	unsigned char status;
	const char *wp_fmt;

	result = sddr09_read_status(us, &status);
	if (result) {
		usb_stor_dbg(us, "read_status fails\n");
		return result;
	}
	if ((status & 0x80) == 0) {
		info->flags |= SDDR09_WP;	/* write protected */
		wp_fmt = " WP";
	} else {
		wp_fmt = "";
	}
	usb_stor_dbg(us, "status 0x%02X%s%s%s%s\n", status, wp_fmt,
		     status & 0x40 ? " Ready" : "",
		     status & LUNBITS ? " Suspended" : "",
		     status & 0x01 ? " Error" : "");

	return 0;
}