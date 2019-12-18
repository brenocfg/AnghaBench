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
struct ses_device {unsigned char* page1_types; unsigned char* page2; int page1_num_types; scalar_t__ page2_len; } ;
struct scsi_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct enclosure_device {struct ses_device* scratch; TYPE_1__ edev; } ;
struct enclosure_component {int number; } ;

/* Variables and functions */
 unsigned char ENCLOSURE_COMPONENT_ARRAY_DEVICE ; 
 unsigned char ENCLOSURE_COMPONENT_DEVICE ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int ses_send_diag (struct scsi_device*,int,unsigned char*,scalar_t__) ; 
 struct scsi_device* to_scsi_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ses_set_page2_descriptor(struct enclosure_device *edev,
				      struct enclosure_component *ecomp,
				      unsigned char *desc)
{
	int i, j, count = 0, descriptor = ecomp->number;
	struct scsi_device *sdev = to_scsi_device(edev->edev.parent);
	struct ses_device *ses_dev = edev->scratch;
	unsigned char *type_ptr = ses_dev->page1_types;
	unsigned char *desc_ptr = ses_dev->page2 + 8;

	/* Clear everything */
	memset(desc_ptr, 0, ses_dev->page2_len - 8);
	for (i = 0; i < ses_dev->page1_num_types; i++, type_ptr += 4) {
		for (j = 0; j < type_ptr[1]; j++) {
			desc_ptr += 4;
			if (type_ptr[0] != ENCLOSURE_COMPONENT_DEVICE &&
			    type_ptr[0] != ENCLOSURE_COMPONENT_ARRAY_DEVICE)
				continue;
			if (count++ == descriptor) {
				memcpy(desc_ptr, desc, 4);
				/* set select */
				desc_ptr[0] |= 0x80;
				/* clear reserved, just in case */
				desc_ptr[0] &= 0xf0;
			}
		}
	}

	return ses_send_diag(sdev, 2, ses_dev->page2, ses_dev->page2_len);
}