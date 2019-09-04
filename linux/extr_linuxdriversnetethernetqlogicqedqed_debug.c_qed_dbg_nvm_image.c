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
typedef  scalar_t__ u32 ;
struct qed_hwfn {int /*<<< orphan*/  cdev; } ;
struct TYPE_2__ {size_t engine_for_debug; } ;
struct qed_dev {TYPE_1__ dbg_params; struct qed_hwfn* hwfns; } ;
typedef  enum qed_nvm_images { ____Placeholder_qed_nvm_images } qed_nvm_images ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (int /*<<< orphan*/ ,char*,int) ; 
 int QED_NVM_IMAGE_NVM_META ; 
 scalar_t__ cpu_to_be32 (scalar_t__) ; 
 int qed_dbg_nvm_image_length (struct qed_hwfn*,int,scalar_t__*) ; 
 int qed_mcp_get_nvm_image (struct qed_hwfn*,int,void*,scalar_t__) ; 
 scalar_t__ roundup (scalar_t__,int) ; 

__attribute__((used)) static int qed_dbg_nvm_image(struct qed_dev *cdev, void *buffer,
			     u32 *num_dumped_bytes,
			     enum qed_nvm_images image_id)
{
	struct qed_hwfn *p_hwfn =
		&cdev->hwfns[cdev->dbg_params.engine_for_debug];
	u32 len_rounded, i;
	__be32 val;
	int rc;

	*num_dumped_bytes = 0;
	rc = qed_dbg_nvm_image_length(p_hwfn, image_id, &len_rounded);
	if (rc)
		return rc;

	DP_NOTICE(p_hwfn->cdev,
		  "Collecting a debug feature [\"nvram image %d\"]\n",
		  image_id);

	len_rounded = roundup(len_rounded, sizeof(u32));
	rc = qed_mcp_get_nvm_image(p_hwfn, image_id, buffer, len_rounded);
	if (rc)
		return rc;

	/* QED_NVM_IMAGE_NVM_META image is not swapped like other images */
	if (image_id != QED_NVM_IMAGE_NVM_META)
		for (i = 0; i < len_rounded; i += 4) {
			val = cpu_to_be32(*(u32 *)(buffer + i));
			*(u32 *)(buffer + i) = val;
		}

	*num_dumped_bytes = len_rounded;

	return rc;
}