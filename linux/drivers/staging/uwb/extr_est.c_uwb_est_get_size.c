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
typedef  size_t u8 ;
struct uwb_rceb {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;
struct uwb_rc {TYPE_1__ uwb_dev; } ;
struct uwb_est_entry {size_t size; unsigned int offset; int type; } ;
struct uwb_est {size_t entries; int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; int /*<<< orphan*/  type_event_high; struct uwb_est_entry* entry; } ;
typedef  size_t ssize_t ;
typedef  int /*<<< orphan*/  __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 size_t ENOENT ; 
 size_t ENOSPC ; 
#define  UWB_EST_16 129 
#define  UWB_EST_8 128 
 int /*<<< orphan*/  dev_err (struct device*,char*,struct uwb_est*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,...) ; 
 size_t le16_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
ssize_t uwb_est_get_size(struct uwb_rc *uwb_rc, struct uwb_est *est,
			 u8 event_low, const struct uwb_rceb *rceb,
			 size_t rceb_size)
{
	unsigned offset;
	ssize_t size;
	struct device *dev = &uwb_rc->uwb_dev.dev;
	const struct uwb_est_entry *entry;

	size = -ENOENT;
	if (event_low >= est->entries) {	/* in range? */
		dev_err(dev, "EST %p 0x%04x/%04x/%04x[%u]: event %u out of range\n",
			est, est->type_event_high, est->vendor, est->product,
			est->entries, event_low);
		goto out;
	}
	size = -ENOENT;
	entry = &est->entry[event_low];
	if (entry->size == 0 && entry->offset == 0) {	/* unknown? */
		dev_err(dev, "EST %p 0x%04x/%04x/%04x[%u]: event %u unknown\n",
			est, est->type_event_high, est->vendor,	est->product,
			est->entries, event_low);
		goto out;
	}
	offset = entry->offset;	/* extra fries with that? */
	if (offset == 0)
		size = entry->size;
	else {
		/* Ops, got an extra size field at 'offset'--read it */
		const void *ptr = rceb;
		size_t type_size = 0;
		offset--;
		size = -ENOSPC;			/* enough data for more? */
		switch (entry->type) {
		case UWB_EST_16:  type_size = sizeof(__le16); break;
		case UWB_EST_8:   type_size = sizeof(u8);     break;
		default: 	 BUG();
		}
		if (offset + type_size > rceb_size) {
			dev_err(dev, "EST %p 0x%04x/%04x/%04x[%u]: "
				"not enough data to read extra size\n",
				est, est->type_event_high, est->vendor,
				est->product, est->entries);
			goto out;
		}
		size = entry->size;
		ptr += offset;
		switch (entry->type) {
		case UWB_EST_16:  size += le16_to_cpu(*(__le16 *)ptr); break;
		case UWB_EST_8:   size += *(u8 *)ptr;                  break;
		default: 	 BUG();
		}
	}
out:
	return size;
}