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
struct uwb_rc {TYPE_1__* ies; } ;
struct uwb_ie_hdr {int element_id; scalar_t__ length; } ;
typedef  enum uwb_ie { ____Placeholder_uwb_ie } uwb_ie ;
struct TYPE_2__ {int /*<<< orphan*/  wIELength; void* IEData; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le16 (size_t) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memmove (struct uwb_ie_hdr*,void*,size_t) ; 
 struct uwb_ie_hdr* uwb_ie_next (void**,size_t*) ; 

__attribute__((used)) static
void uwb_rc_ie_cache_rm(struct uwb_rc *uwb_rc, enum uwb_ie to_remove)
{
	struct uwb_ie_hdr *ie;
	size_t len = le16_to_cpu(uwb_rc->ies->wIELength);
	void *ptr;
	size_t size;

	ptr = uwb_rc->ies->IEData;
	size = len;
	for (;;) {
		ie = uwb_ie_next(&ptr, &size);
		if (!ie)
			break;
		if (ie->element_id == to_remove) {
			len -= sizeof(struct uwb_ie_hdr) + ie->length;
			memmove(ie, ptr, size);
			ptr = ie;
		}
	}
	uwb_rc->ies->wIELength = cpu_to_le16(len);
}