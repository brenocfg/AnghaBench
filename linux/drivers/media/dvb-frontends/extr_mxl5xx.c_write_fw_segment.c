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
typedef  scalar_t__ u32 ;
struct mxl {int dummy; } ;

/* Variables and functions */
 int MXL_HYDRA_I2C_HDR_SIZE ; 
 int MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH ; 
 int MXL_HYDRA_REG_SIZE_IN_BYTES ; 
 int /*<<< orphan*/  convert_endian (int,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,scalar_t__) ; 
 int write_firmware_block (struct mxl*,scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_fw_segment(struct mxl *state,
			    u32 mem_addr, u32 total_size, u8 *data_ptr)
{
	int status;
	u32 data_count = 0;
	u32 size = 0;
	u32 orig_size = 0;
	u8 *w_buf_ptr = NULL;
	u32 block_size = ((MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH -
			 (MXL_HYDRA_I2C_HDR_SIZE +
			  MXL_HYDRA_REG_SIZE_IN_BYTES)) / 4) * 4;
	u8 w_msg_buffer[MXL_HYDRA_OEM_MAX_BLOCK_WRITE_LENGTH -
		      (MXL_HYDRA_I2C_HDR_SIZE + MXL_HYDRA_REG_SIZE_IN_BYTES)];

	do {
		size = orig_size = (((u32)(data_count + block_size)) > total_size) ?
			(total_size - data_count) : block_size;

		if (orig_size & 3)
			size = (orig_size + 4) & ~3;
		w_buf_ptr = &w_msg_buffer[0];
		memset((void *) w_buf_ptr, 0, size);
		memcpy((void *) w_buf_ptr, (void *) data_ptr, orig_size);
		convert_endian(1, size, w_buf_ptr);
		status  = write_firmware_block(state, mem_addr, size, w_buf_ptr);
		if (status)
			return status;
		data_count += size;
		mem_addr   += size;
		data_ptr   += size;
	} while (data_count < total_size);

	return status;
}