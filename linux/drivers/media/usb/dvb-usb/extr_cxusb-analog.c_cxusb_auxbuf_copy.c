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
struct cxusb_medion_auxbuf {unsigned int paylen; scalar_t__ buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,scalar_t__,unsigned int) ; 

__attribute__((used)) static bool cxusb_auxbuf_copy(struct cxusb_medion_auxbuf *auxbuf,
			      unsigned int pos, unsigned char *dest,
			      unsigned int len)
{
	if (pos + len > auxbuf->paylen)
		return false;

	memcpy(dest, auxbuf->buf + pos, len);

	return true;
}