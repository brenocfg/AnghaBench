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
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct bin_buffer_hdr {int offset; int /*<<< orphan*/  length; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
struct TYPE_2__ {int /*<<< orphan*/  size_in_dwords; int /*<<< orphan*/ * ptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BYTES_TO_DWORDS (int /*<<< orphan*/ ) ; 
 int DBG_STATUS_OK ; 
 size_t MAX_BIN_DBG_BUFFER_TYPE ; 
 TYPE_1__* s_user_dbg_arrays ; 

enum dbg_status qed_dbg_user_set_bin_ptr(const u8 * const bin_ptr)
{
	struct bin_buffer_hdr *buf_array = (struct bin_buffer_hdr *)bin_ptr;
	u8 buf_id;

	/* Convert binary data to debug arrays */
	for (buf_id = 0; buf_id < MAX_BIN_DBG_BUFFER_TYPE; buf_id++) {
		s_user_dbg_arrays[buf_id].ptr =
			(u32 *)(bin_ptr + buf_array[buf_id].offset);
		s_user_dbg_arrays[buf_id].size_in_dwords =
			BYTES_TO_DWORDS(buf_array[buf_id].length);
	}

	return DBG_STATUS_OK;
}