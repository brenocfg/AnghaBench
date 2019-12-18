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
struct iscsi_bus_flash_session {int target_id; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct iscsi_bus_flash_session* iscsi_dev_to_flash_session (struct device*) ; 
 int /*<<< orphan*/  iscsi_flashnode_bus_match (struct device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int flashnode_match_index(struct device *dev, void *data)
{
	struct iscsi_bus_flash_session *fnode_sess = NULL;
	int ret = 0;

	if (!iscsi_flashnode_bus_match(dev, NULL))
		goto exit_match_index;

	fnode_sess = iscsi_dev_to_flash_session(dev);
	ret = (fnode_sess->target_id == *((int *)data)) ? 1 : 0;

exit_match_index:
	return ret;
}