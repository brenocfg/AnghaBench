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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ice_hw {int /*<<< orphan*/  pkg_size; int /*<<< orphan*/ * pkg_copy; } ;
typedef  enum ice_status { ____Placeholder_ice_status } ice_status ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int ICE_ERR_PARAM ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * devm_kmemdup (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ice_hw_to_dev (struct ice_hw*) ; 
 int ice_init_pkg (struct ice_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

enum ice_status ice_copy_and_init_pkg(struct ice_hw *hw, const u8 *buf, u32 len)
{
	enum ice_status status;
	u8 *buf_copy;

	if (!buf || !len)
		return ICE_ERR_PARAM;

	buf_copy = devm_kmemdup(ice_hw_to_dev(hw), buf, len, GFP_KERNEL);

	status = ice_init_pkg(hw, buf_copy, len);
	if (status) {
		/* Free the copy, since we failed to initialize the package */
		devm_kfree(ice_hw_to_dev(hw), buf_copy);
	} else {
		/* Track the copied pkg so we can free it later */
		hw->pkg_copy = buf_copy;
		hw->pkg_size = len;
	}

	return status;
}