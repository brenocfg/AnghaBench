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
struct cxl_adapter_image {int dummy; } ;
struct cxl {int slices; TYPE_1__* guest; int /*<<< orphan*/ * afu; } ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEVICE_SCOPE ; 
#define  DOWNLOAD_IMAGE 129 
 int EINVAL ; 
#define  VALIDATE_IMAGE 128 
 int /*<<< orphan*/  cxl_guest_remove_afu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_h_download_adapter_image ; 
 int /*<<< orphan*/  cxl_h_reset_adapter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxl_h_validate_adapter_image ; 
 int handle_image (struct cxl*,int,int /*<<< orphan*/ *,struct cxl_adapter_image*) ; 
 int /*<<< orphan*/  pr_devel (char*) ; 
 int transfer ; 
 int update_devicetree (struct cxl*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int transfer_image(struct cxl *adapter, int operation,
			struct cxl_adapter_image *ai)
{
	int rc = 0;
	int afu;

	switch (operation) {
	case DOWNLOAD_IMAGE:
		rc = handle_image(adapter, operation,
				&cxl_h_download_adapter_image, ai);
		if (rc < 0) {
			pr_devel("resetting adapter\n");
			cxl_h_reset_adapter(adapter->guest->handle);
		}
		return rc;

	case VALIDATE_IMAGE:
		rc = handle_image(adapter, operation,
				&cxl_h_validate_adapter_image, ai);
		if (rc < 0) {
			pr_devel("resetting adapter\n");
			cxl_h_reset_adapter(adapter->guest->handle);
			return rc;
		}
		if (rc == 0) {
			pr_devel("remove current afu\n");
			for (afu = 0; afu < adapter->slices; afu++)
				cxl_guest_remove_afu(adapter->afu[afu]);

			pr_devel("resetting adapter\n");
			cxl_h_reset_adapter(adapter->guest->handle);

			/* The entire image has now been
			 * downloaded and the validation has
			 * been successfully performed.
			 * After that, the partition should call
			 * ibm,update-nodes and
			 * ibm,update-properties to receive the
			 * current configuration
			 */
			rc = update_devicetree(adapter, DEVICE_SCOPE);
			transfer = 1;
		}
		return rc;
	}

	return -EINVAL;
}