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
typedef  int u64 ;
struct cper_record_header {int record_length; } ;
typedef  int ssize_t ;
struct TYPE_2__ {struct cper_record_header* vaddr; } ;

/* Variables and functions */
 int __erst_read_to_erange (int,int*) ; 
 TYPE_1__ erst_erange ; 
 int /*<<< orphan*/  memcpy (struct cper_record_header*,struct cper_record_header*,int) ; 

__attribute__((used)) static ssize_t __erst_read(u64 record_id, struct cper_record_header *record,
			   size_t buflen)
{
	int rc;
	u64 offset, len = 0;
	struct cper_record_header *rcd_tmp;

	rc = __erst_read_to_erange(record_id, &offset);
	if (rc)
		return rc;
	rcd_tmp = erst_erange.vaddr + offset;
	len = rcd_tmp->record_length;
	if (len <= buflen)
		memcpy(record, rcd_tmp, len);

	return len;
}