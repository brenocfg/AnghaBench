#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_3__ {int /*<<< orphan*/  (* release_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;scalar_t__ (* acquire_swfw_sync ) (struct ixgbe_hw*,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {TYPE_1__ ops; } ;
struct ixgbe_hw {TYPE_2__ mac; } ;
struct ixgbe_hic_hdr {scalar_t__ buf_len; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ IXGBE_ERR_HOST_INTERFACE_COMMAND ; 
 int /*<<< orphan*/  IXGBE_FLEX_MNG ; 
 int /*<<< orphan*/  IXGBE_GSSR_SW_MNG_SM ; 
 scalar_t__ IXGBE_HI_MAX_BLOCK_BYTE_LENGTH ; 
 void* IXGBE_READ_REG_ARRAY (struct ixgbe_hw*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*,...) ; 
 scalar_t__ ixgbe_hic_unlocked (struct ixgbe_hw*,void*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  le32_to_cpus (scalar_t__*) ; 
 scalar_t__ round_up (scalar_t__,int) ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 

s32 ixgbe_host_interface_command(struct ixgbe_hw *hw, void *buffer,
				 u32 length, u32 timeout,
				 bool return_data)
{
	u32 hdr_size = sizeof(struct ixgbe_hic_hdr);
	union {
		struct ixgbe_hic_hdr hdr;
		u32 u32arr[1];
	} *bp = buffer;
	u16 buf_len, dword_len;
	s32 status;
	u32 bi;

	if (!length || length > IXGBE_HI_MAX_BLOCK_BYTE_LENGTH) {
		hw_dbg(hw, "Buffer length failure buffersize-%d.\n", length);
		return IXGBE_ERR_HOST_INTERFACE_COMMAND;
	}
	/* Take management host interface semaphore */
	status = hw->mac.ops.acquire_swfw_sync(hw, IXGBE_GSSR_SW_MNG_SM);
	if (status)
		return status;

	status = ixgbe_hic_unlocked(hw, buffer, length, timeout);
	if (status)
		goto rel_out;

	if (!return_data)
		goto rel_out;

	/* Calculate length in DWORDs */
	dword_len = hdr_size >> 2;

	/* first pull in the header so we know the buffer length */
	for (bi = 0; bi < dword_len; bi++) {
		bp->u32arr[bi] = IXGBE_READ_REG_ARRAY(hw, IXGBE_FLEX_MNG, bi);
		le32_to_cpus(&bp->u32arr[bi]);
	}

	/* If there is any thing in data position pull it in */
	buf_len = bp->hdr.buf_len;
	if (!buf_len)
		goto rel_out;

	if (length < round_up(buf_len, 4) + hdr_size) {
		hw_dbg(hw, "Buffer not large enough for reply message.\n");
		status = IXGBE_ERR_HOST_INTERFACE_COMMAND;
		goto rel_out;
	}

	/* Calculate length in DWORDs, add 3 for odd lengths */
	dword_len = (buf_len + 3) >> 2;

	/* Pull in the rest of the buffer (bi is where we left off) */
	for (; bi <= dword_len; bi++) {
		bp->u32arr[bi] = IXGBE_READ_REG_ARRAY(hw, IXGBE_FLEX_MNG, bi);
		le32_to_cpus(&bp->u32arr[bi]);
	}

rel_out:
	hw->mac.ops.release_swfw_sync(hw, IXGBE_GSSR_SW_MNG_SM);

	return status;
}