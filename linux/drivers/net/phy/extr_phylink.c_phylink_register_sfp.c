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
struct phylink {int /*<<< orphan*/  sfp_bus; } ;
struct fwnode_reference_args {int /*<<< orphan*/  fwnode; } ;
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int fwnode_property_get_reference_args (struct fwnode_handle*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fwnode_reference_args*) ; 
 int /*<<< orphan*/  phylink_err (struct phylink*,char*,int) ; 
 int /*<<< orphan*/  sfp_phylink_ops ; 
 int /*<<< orphan*/  sfp_register_upstream (int /*<<< orphan*/ ,struct phylink*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int phylink_register_sfp(struct phylink *pl,
				struct fwnode_handle *fwnode)
{
	struct fwnode_reference_args ref;
	int ret;

	if (!fwnode)
		return 0;

	ret = fwnode_property_get_reference_args(fwnode, "sfp", NULL,
						 0, 0, &ref);
	if (ret < 0) {
		if (ret == -ENOENT)
			return 0;

		phylink_err(pl, "unable to parse \"sfp\" node: %d\n",
			    ret);
		return ret;
	}

	pl->sfp_bus = sfp_register_upstream(ref.fwnode, pl, &sfp_phylink_ops);
	if (!pl->sfp_bus)
		return -ENOMEM;

	return 0;
}