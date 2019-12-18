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
struct sun6i_csi_dev {int dummy; } ;
struct sun6i_csi_config {int dummy; } ;
struct sun6i_csi {int /*<<< orphan*/  config; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct sun6i_csi_config*,int) ; 
 int /*<<< orphan*/  sun6i_csi_set_format (struct sun6i_csi_dev*) ; 
 int /*<<< orphan*/  sun6i_csi_set_window (struct sun6i_csi_dev*) ; 
 int /*<<< orphan*/  sun6i_csi_setup_bus (struct sun6i_csi_dev*) ; 
 struct sun6i_csi_dev* sun6i_csi_to_dev (struct sun6i_csi*) ; 

int sun6i_csi_update_config(struct sun6i_csi *csi,
			    struct sun6i_csi_config *config)
{
	struct sun6i_csi_dev *sdev = sun6i_csi_to_dev(csi);

	if (!config)
		return -EINVAL;

	memcpy(&csi->config, config, sizeof(csi->config));

	sun6i_csi_setup_bus(sdev);
	sun6i_csi_set_format(sdev);
	sun6i_csi_set_window(sdev);

	return 0;
}