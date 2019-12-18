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

/* Variables and functions */
 char* scsi_extd_sense_format (unsigned char,unsigned char,char const**) ; 
 char* scsi_sense_key_string (unsigned char) ; 
 int /*<<< orphan*/  usb_stor_dbg (struct us_data const*,char*,char const*,char const*,...) ; 

void usb_stor_show_sense(const struct us_data *us,
			 unsigned char key,
			 unsigned char asc,
			 unsigned char ascq)
{
	const char *what, *keystr, *fmt;

	keystr = scsi_sense_key_string(key);
	what = scsi_extd_sense_format(asc, ascq, &fmt);

	if (keystr == NULL)
		keystr = "(Unknown Key)";
	if (what == NULL)
		what = "(unknown ASC/ASCQ)";

	if (fmt)
		usb_stor_dbg(us, "%s: %s (%s%x)\n", keystr, what, fmt, ascq);
	else
		usb_stor_dbg(us, "%s: %s\n", keystr, what);
}