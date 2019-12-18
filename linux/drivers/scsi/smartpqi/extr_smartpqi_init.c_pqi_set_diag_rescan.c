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
struct pqi_ctrl_info {int dummy; } ;
struct bmic_diag_options {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int /*<<< orphan*/  BMIC_SENSE_DIAG_OPTIONS ; 
 int /*<<< orphan*/  BMIC_SET_DIAG_OPTIONS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PQI_FETCH_PTRAID_DATA ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct bmic_diag_options*) ; 
 struct bmic_diag_options* kzalloc (int,int /*<<< orphan*/ ) ; 
 int pqi_send_ctrl_raid_request (struct pqi_ctrl_info*,int /*<<< orphan*/ ,struct bmic_diag_options*,int) ; 

__attribute__((used)) static int pqi_set_diag_rescan(struct pqi_ctrl_info *ctrl_info)
{
	int rc;
	struct bmic_diag_options *diag;

	diag = kzalloc(sizeof(*diag), GFP_KERNEL);
	if (!diag)
		return -ENOMEM;

	rc = pqi_send_ctrl_raid_request(ctrl_info, BMIC_SENSE_DIAG_OPTIONS,
					diag, sizeof(*diag));
	if (rc)
		goto out;

	diag->options |= cpu_to_le32(PQI_FETCH_PTRAID_DATA);

	rc = pqi_send_ctrl_raid_request(ctrl_info, BMIC_SET_DIAG_OPTIONS,
					diag, sizeof(*diag));
out:
	kfree(diag);

	return rc;
}