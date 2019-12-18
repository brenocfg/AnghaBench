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
typedef  scalar_t__ u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct fman_sp_int_context_data_copy {int ext_buf_offset; int size; scalar_t__ int_context_offset; } ;
struct fman_sp_buffer_offsets {int prs_result_offset; int time_stamp_offset; int hash_result_offset; int data_offset; } ;
struct fman_sp_buf_margins {int start_margins; } ;
struct fman_prs_result {int dummy; } ;
struct fman_buffer_prefix_content {int priv_data_size; int data_align; scalar_t__ pass_prs_result; scalar_t__ pass_hash_result; scalar_t__ pass_time_stamp; } ;

/* Variables and functions */
 scalar_t__ ILLEGAL_BASE ; 
 int OFFSET_UNITS ; 

int fman_sp_build_buffer_struct(struct fman_sp_int_context_data_copy *
				int_context_data_copy,
				struct fman_buffer_prefix_content *
				buffer_prefix_content,
				struct fman_sp_buf_margins *buf_margins,
				struct fman_sp_buffer_offsets *buffer_offsets,
				u8 *internal_buf_offset)
{
	u32 tmp;

	/* Align start of internal context data to 16 byte */
	int_context_data_copy->ext_buf_offset = (u16)
		((buffer_prefix_content->priv_data_size & (OFFSET_UNITS - 1)) ?
		((buffer_prefix_content->priv_data_size + OFFSET_UNITS) &
			~(u16)(OFFSET_UNITS - 1)) :
		buffer_prefix_content->priv_data_size);

	/* Translate margin and int_context params to FM parameters */
	/* Initialize with illegal value. Later we'll set legal values. */
	buffer_offsets->prs_result_offset = (u32)ILLEGAL_BASE;
	buffer_offsets->time_stamp_offset = (u32)ILLEGAL_BASE;
	buffer_offsets->hash_result_offset = (u32)ILLEGAL_BASE;

	/* Internally the driver supports 4 options
	 * 1. prsResult/timestamp/hashResult selection (in fact 8 options,
	 * but for simplicity we'll
	 * relate to it as 1).
	 * 2. All IC context (from AD) not including debug.
	 */

	/* This case covers the options under 1 */
	/* Copy size must be in 16-byte granularity. */
	int_context_data_copy->size =
	    (u16)((buffer_prefix_content->pass_prs_result ? 32 : 0) +
		  ((buffer_prefix_content->pass_time_stamp ||
		  buffer_prefix_content->pass_hash_result) ? 16 : 0));

	/* Align start of internal context data to 16 byte */
	int_context_data_copy->int_context_offset =
	    (u8)(buffer_prefix_content->pass_prs_result ? 32 :
		 ((buffer_prefix_content->pass_time_stamp ||
		 buffer_prefix_content->pass_hash_result) ? 64 : 0));

	if (buffer_prefix_content->pass_prs_result)
		buffer_offsets->prs_result_offset =
		    int_context_data_copy->ext_buf_offset;
	if (buffer_prefix_content->pass_time_stamp)
		buffer_offsets->time_stamp_offset =
		    buffer_prefix_content->pass_prs_result ?
		    (int_context_data_copy->ext_buf_offset +
			sizeof(struct fman_prs_result)) :
		    int_context_data_copy->ext_buf_offset;
	if (buffer_prefix_content->pass_hash_result)
		/* If PR is not requested, whether TS is
		 * requested or not, IC will be copied from TS
			 */
		buffer_offsets->hash_result_offset =
		buffer_prefix_content->pass_prs_result ?
			(int_context_data_copy->ext_buf_offset +
				sizeof(struct fman_prs_result) + 8) :
			int_context_data_copy->ext_buf_offset + 8;

	if (int_context_data_copy->size)
		buf_margins->start_margins =
		    (u16)(int_context_data_copy->ext_buf_offset +
			  int_context_data_copy->size);
	else
		/* No Internal Context passing, STartMargin is
		 * immediately after private_info
		 */
		buf_margins->start_margins =
		    buffer_prefix_content->priv_data_size;

	/* align data start */
	tmp = (u32)(buf_margins->start_margins %
		    buffer_prefix_content->data_align);
	if (tmp)
		buf_margins->start_margins +=
		    (buffer_prefix_content->data_align - tmp);
	buffer_offsets->data_offset = buf_margins->start_margins;

	return 0;
}