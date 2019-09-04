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
typedef  union init_op {int dummy; } init_op ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct qed_fw_data {int* arr_data; int init_ops_size; int /*<<< orphan*/ * modes_tree_buf; union init_op* init_ops; struct fw_ver_info* fw_ver_info; } ;
struct qed_dev {struct qed_fw_data* fw_data; } ;
struct init_raw_op {int dummy; } ;
struct fw_ver_info {int dummy; } ;
struct bin_buffer_hdr {int offset; int length; } ;

/* Variables and functions */
 size_t BIN_BUF_INIT_CMD ; 
 size_t BIN_BUF_INIT_FW_VER_INFO ; 
 size_t BIN_BUF_INIT_MODE_TREE ; 
 size_t BIN_BUF_INIT_VAL ; 
 int /*<<< orphan*/  DP_NOTICE (struct qed_dev*,char*) ; 
 int EINVAL ; 

int qed_init_fw_data(struct qed_dev *cdev, const u8 *data)
{
	struct qed_fw_data *fw = cdev->fw_data;
	struct bin_buffer_hdr *buf_hdr;
	u32 offset, len;

	if (!data) {
		DP_NOTICE(cdev, "Invalid fw data\n");
		return -EINVAL;
	}

	/* First Dword contains metadata and should be skipped */
	buf_hdr = (struct bin_buffer_hdr *)data;

	offset = buf_hdr[BIN_BUF_INIT_FW_VER_INFO].offset;
	fw->fw_ver_info = (struct fw_ver_info *)(data + offset);

	offset = buf_hdr[BIN_BUF_INIT_CMD].offset;
	fw->init_ops = (union init_op *)(data + offset);

	offset = buf_hdr[BIN_BUF_INIT_VAL].offset;
	fw->arr_data = (u32 *)(data + offset);

	offset = buf_hdr[BIN_BUF_INIT_MODE_TREE].offset;
	fw->modes_tree_buf = (u8 *)(data + offset);
	len = buf_hdr[BIN_BUF_INIT_CMD].length;
	fw->init_ops_size = len / sizeof(struct init_raw_op);

	return 0;
}