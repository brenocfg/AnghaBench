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
typedef  int u8 ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int const BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int const) ; 
 int /*<<< orphan*/  NETIF_MSG_DRV ; 
 int qed_mcp_nvm_put_file_begin (struct qed_dev*,int const) ; 

__attribute__((used)) static int qed_nvm_flash_image_file_start(struct qed_dev *cdev,
					  const u8 **data, bool *check_resp)
{
	int rc;

	*data += 4;
	*check_resp = !!(**data & BIT(0));
	*data += 4;

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "About to start a new file of type %02x\n", **data);
	rc = qed_mcp_nvm_put_file_begin(cdev, **data);
	*data += 4;

	return rc;
}