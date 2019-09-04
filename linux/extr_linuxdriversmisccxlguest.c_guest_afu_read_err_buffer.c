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
typedef  int /*<<< orphan*/  u64 ;
struct cxl_afu {TYPE_1__* guest; } ;
typedef  int ssize_t ;
typedef  int loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ENOMEM ; 
 size_t ERR_BUFF_MAX_COPY_SIZE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int cxl_h_get_afu_err (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  free_page (int /*<<< orphan*/ ) ; 
 scalar_t__ get_zeroed_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,void*,size_t) ; 
 int /*<<< orphan*/  virt_to_phys (void*) ; 

__attribute__((used)) static ssize_t guest_afu_read_err_buffer(struct cxl_afu *afu, char *buf,
					loff_t off, size_t count)
{
	void *tbuf = NULL;
	int rc = 0;

	tbuf = (void *) get_zeroed_page(GFP_KERNEL);
	if (!tbuf)
		return -ENOMEM;

	rc = cxl_h_get_afu_err(afu->guest->handle,
			       off & 0x7,
			       virt_to_phys(tbuf),
			       count);
	if (rc)
		goto err;

	if (count > ERR_BUFF_MAX_COPY_SIZE)
		count = ERR_BUFF_MAX_COPY_SIZE - (off & 0x7);
	memcpy(buf, tbuf, count);
err:
	free_page((u64)tbuf);

	return rc;
}