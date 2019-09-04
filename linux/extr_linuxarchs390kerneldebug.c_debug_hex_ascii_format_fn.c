#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct debug_view {int dummy; } ;
struct TYPE_3__ {int buf_size; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 scalar_t__ isascii (unsigned char) ; 
 scalar_t__ isprint (unsigned char) ; 
 scalar_t__ sprintf (char*,char*,...) ; 

__attribute__((used)) static int debug_hex_ascii_format_fn(debug_info_t *id, struct debug_view *view,
				     char *out_buf, const char *in_buf)
{
	int i, rc = 0;

	for (i = 0; i < id->buf_size; i++)
		rc += sprintf(out_buf + rc, "%02x ", ((unsigned char *) in_buf)[i]);
	rc += sprintf(out_buf + rc, "| ");
	for (i = 0; i < id->buf_size; i++) {
		unsigned char c = in_buf[i];

		if (isascii(c) && isprint(c))
			rc += sprintf(out_buf + rc, "%c", c);
		else
			rc += sprintf(out_buf + rc, ".");
	}
	rc += sprintf(out_buf + rc, "\n");
	return rc;
}