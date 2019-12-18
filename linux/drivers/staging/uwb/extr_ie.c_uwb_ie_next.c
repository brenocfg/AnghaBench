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
struct uwb_ie_hdr {int length; } ;

/* Variables and functions */

struct uwb_ie_hdr *uwb_ie_next(void **ptr, size_t *len)
{
	struct uwb_ie_hdr *hdr;
	size_t ie_len;

	if (*len < sizeof(struct uwb_ie_hdr))
		return NULL;

	hdr = *ptr;
	ie_len = sizeof(struct uwb_ie_hdr) + hdr->length;

	if (*len < ie_len)
		return NULL;

	*ptr += ie_len;
	*len -= ie_len;

	return hdr;
}