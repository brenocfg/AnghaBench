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
struct msm_dsi_host {int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  id; int /*<<< orphan*/  power_on; } ;
struct mipi_dsi_msg {int dummy; } ;
struct mipi_dsi_host {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int msm_dsi_manager_cmd_xfer (int /*<<< orphan*/ ,struct mipi_dsi_msg const*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct msm_dsi_host* to_msm_dsi_host (struct mipi_dsi_host*) ; 

__attribute__((used)) static ssize_t dsi_host_transfer(struct mipi_dsi_host *host,
					const struct mipi_dsi_msg *msg)
{
	struct msm_dsi_host *msm_host = to_msm_dsi_host(host);
	int ret;

	if (!msg || !msm_host->power_on)
		return -EINVAL;

	mutex_lock(&msm_host->cmd_mutex);
	ret = msm_dsi_manager_cmd_xfer(msm_host->id, msg);
	mutex_unlock(&msm_host->cmd_mutex);

	return ret;
}