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
struct pqi_general_admin_response {int dummy; } ;
struct pqi_admin_queues {int oq_ci_copy; int /*<<< orphan*/  oq_ci; scalar_t__ oq_element_array; int /*<<< orphan*/  oq_pi; } ;
struct pqi_ctrl_info {TYPE_1__* pci_dev; struct pqi_admin_queues admin_queues; } ;
typedef  int pqi_index_t ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int ETIMEDOUT ; 
 int PQI_ADMIN_OQ_ELEMENT_LENGTH ; 
 int PQI_ADMIN_OQ_NUM_ELEMENTS ; 
 unsigned long PQI_ADMIN_REQUEST_TIMEOUT_SECS ; 
 unsigned long PQI_HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int /*<<< orphan*/  memcpy (struct pqi_general_admin_response*,scalar_t__,int) ; 
 int readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis_is_firmware_running (struct pqi_ctrl_info*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pqi_poll_for_admin_response(struct pqi_ctrl_info *ctrl_info,
	struct pqi_general_admin_response *response)
{
	struct pqi_admin_queues *admin_queues;
	pqi_index_t oq_pi;
	pqi_index_t oq_ci;
	unsigned long timeout;

	admin_queues = &ctrl_info->admin_queues;
	oq_ci = admin_queues->oq_ci_copy;

	timeout = (PQI_ADMIN_REQUEST_TIMEOUT_SECS * PQI_HZ) + jiffies;

	while (1) {
		oq_pi = readl(admin_queues->oq_pi);
		if (oq_pi != oq_ci)
			break;
		if (time_after(jiffies, timeout)) {
			dev_err(&ctrl_info->pci_dev->dev,
				"timed out waiting for admin response\n");
			return -ETIMEDOUT;
		}
		if (!sis_is_firmware_running(ctrl_info))
			return -ENXIO;
		usleep_range(1000, 2000);
	}

	memcpy(response, admin_queues->oq_element_array +
		(oq_ci * PQI_ADMIN_OQ_ELEMENT_LENGTH), sizeof(*response));

	oq_ci = (oq_ci + 1) % PQI_ADMIN_OQ_NUM_ELEMENTS;
	admin_queues->oq_ci_copy = oq_ci;
	writel(oq_ci, admin_queues->oq_ci);

	return 0;
}