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
typedef  scalar_t__ u32 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {scalar_t__ word_size; } ;
struct ixgbe_hw {TYPE_1__ eeprom; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ IXGBE_ERR_PARAM ; 
 int /*<<< orphan*/  hw_dbg (struct ixgbe_hw*,char*) ; 
 scalar_t__ ixgbe_read_ee_hostif_buffer_X550 (struct ixgbe_hw*,scalar_t__,scalar_t__,scalar_t__*) ; 

__attribute__((used)) static s32 ixgbe_checksum_ptr_x550(struct ixgbe_hw *hw, u16 ptr,
				   u16 size, u16 *csum, u16 *buffer,
				   u32 buffer_size)
{
	u16 buf[256];
	s32 status;
	u16 length, bufsz, i, start;
	u16 *local_buffer;

	bufsz = ARRAY_SIZE(buf);

	/* Read a chunk at the pointer location */
	if (!buffer) {
		status = ixgbe_read_ee_hostif_buffer_X550(hw, ptr, bufsz, buf);
		if (status) {
			hw_dbg(hw, "Failed to read EEPROM image\n");
			return status;
		}
		local_buffer = buf;
	} else {
		if (buffer_size < ptr)
			return  IXGBE_ERR_PARAM;
		local_buffer = &buffer[ptr];
	}

	if (size) {
		start = 0;
		length = size;
	} else {
		start = 1;
		length = local_buffer[0];

		/* Skip pointer section if length is invalid. */
		if (length == 0xFFFF || length == 0 ||
		    (ptr + length) >= hw->eeprom.word_size)
			return 0;
	}

	if (buffer && ((u32)start + (u32)length > buffer_size))
		return IXGBE_ERR_PARAM;

	for (i = start; length; i++, length--) {
		if (i == bufsz && !buffer) {
			ptr += bufsz;
			i = 0;
			if (length < bufsz)
				bufsz = length;

			/* Read a chunk at the pointer location */
			status = ixgbe_read_ee_hostif_buffer_X550(hw, ptr,
								  bufsz, buf);
			if (status) {
				hw_dbg(hw, "Failed to read EEPROM image\n");
				return status;
			}
		}
		*csum += local_buffer[i];
	}
	return 0;
}