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
typedef  int /*<<< orphan*/  u8 ;

/* Variables and functions */
 int USB_DT_STRING ; 
 int strlen (char const*) ; 

__attribute__((used)) static unsigned
ascii2desc(char const *s, u8 *buf, unsigned len)
{
	unsigned n, t = 2 + 2*strlen(s);

	if (t > 254)
		t = 254;	/* Longest possible UTF string descriptor */
	if (len > t)
		len = t;

	t += USB_DT_STRING << 8;	/* Now t is first 16 bits to store */

	n = len;
	while (n--) {
		*buf++ = t;
		if (!n--)
			break;
		*buf++ = t >> 8;
		t = (unsigned char)*s++;
	}
	return len;
}