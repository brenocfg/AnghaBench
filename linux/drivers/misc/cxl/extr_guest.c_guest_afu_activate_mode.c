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
struct cxl_afu {int modes_supported; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CXL_MODE_DEDICATED ; 
 int CXL_MODE_DIRECTED ; 
 int EINVAL ; 
 int activate_afu_directed (struct cxl_afu*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int guest_afu_activate_mode(struct cxl_afu *afu, int mode)
{
	if (!mode)
		return 0;
	if (!(mode & afu->modes_supported))
		return -EINVAL;

	if (mode == CXL_MODE_DIRECTED)
		return activate_afu_directed(afu);

	if (mode == CXL_MODE_DEDICATED)
		dev_err(&afu->dev, "Dedicated mode not supported\n");

	return -EINVAL;
}