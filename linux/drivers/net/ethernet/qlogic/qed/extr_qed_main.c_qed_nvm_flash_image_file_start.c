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
typedef  int u32 ;
struct qed_dev {int dummy; } ;

/* Variables and functions */
 int const BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_VERBOSE (struct qed_dev*,int /*<<< orphan*/ ,char*,int) ; 
 int DRV_MB_PARAM_NVM_PUT_FILE_BEGIN_MBI ; 
 int /*<<< orphan*/  NETIF_MSG_DRV ; 
 int /*<<< orphan*/  QED_PUT_FILE_BEGIN ; 
 int qed_mcp_nvm_write (struct qed_dev*,int /*<<< orphan*/ ,int,int*,int) ; 

__attribute__((used)) static int qed_nvm_flash_image_file_start(struct qed_dev *cdev,
					  const u8 **data, bool *check_resp)
{
	u32 file_type, file_size = 0;
	int rc;

	*data += 4;
	*check_resp = !!(**data & BIT(0));
	*data += 4;
	file_type = **data;

	DP_VERBOSE(cdev, NETIF_MSG_DRV,
		   "About to start a new file of type %02x\n", file_type);
	if (file_type == DRV_MB_PARAM_NVM_PUT_FILE_BEGIN_MBI) {
		*data += 4;
		file_size = *((u32 *)(*data));
	}

	rc = qed_mcp_nvm_write(cdev, QED_PUT_FILE_BEGIN, file_type,
			       (u8 *)(&file_size), 4);
	*data += 4;

	return rc;
}