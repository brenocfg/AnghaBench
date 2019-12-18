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
struct uclogic_params {unsigned int desc_size; int /*<<< orphan*/ * desc_ptr; } ;
struct hid_device {unsigned int dev_rsize; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  hid_dbg (struct hid_device*,char*,...) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmemdup (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct uclogic_params*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int uclogic_params_init_with_opt_desc(struct uclogic_params *params,
					     struct hid_device *hdev,
					     unsigned int orig_desc_size,
					     __u8 *desc_ptr,
					     unsigned int desc_size)
{
	__u8 *desc_copy_ptr = NULL;
	unsigned int desc_copy_size;
	int rc;

	/* Check arguments */
	if (params == NULL || hdev == NULL ||
	    (desc_ptr == NULL && desc_size != 0)) {
		rc = -EINVAL;
		goto cleanup;
	}

	/* Replace report descriptor, if it matches */
	if (hdev->dev_rsize == orig_desc_size) {
		hid_dbg(hdev,
			"device report descriptor matches the expected size, replacing\n");
		desc_copy_ptr = kmemdup(desc_ptr, desc_size, GFP_KERNEL);
		if (desc_copy_ptr == NULL) {
			rc = -ENOMEM;
			goto cleanup;
		}
		desc_copy_size = desc_size;
	} else {
		hid_dbg(hdev,
			"device report descriptor doesn't match the expected size (%u != %u), preserving\n",
			hdev->dev_rsize, orig_desc_size);
		desc_copy_ptr = NULL;
		desc_copy_size = 0;
	}

	/* Output parameters */
	memset(params, 0, sizeof(*params));
	params->desc_ptr = desc_copy_ptr;
	desc_copy_ptr = NULL;
	params->desc_size = desc_copy_size;

	rc = 0;
cleanup:
	kfree(desc_copy_ptr);
	return rc;
}