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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct mcp_trace_format {scalar_t__ data; char* format_str; } ;
typedef  enum dbg_status { ____Placeholder_dbg_status } dbg_status ;
struct TYPE_2__ {scalar_t__ formats_num; char** modules; struct mcp_trace_format* formats; } ;

/* Variables and functions */
 scalar_t__ ARRAY_SIZE (char**) ; 
 int DBG_STATUS_MCP_TRACE_BAD_DATA ; 
 int DBG_STATUS_OK ; 
 int MCP_TRACE_FORMAT_LEVEL_MASK ; 
 int MCP_TRACE_FORMAT_LEVEL_SHIFT ; 
 scalar_t__ MCP_TRACE_FORMAT_MAX_PARAMS ; 
 int MCP_TRACE_FORMAT_MODULE_MASK ; 
 int MCP_TRACE_FORMAT_MODULE_SHIFT ; 
 scalar_t__ MCP_TRACE_FORMAT_P1_SIZE_MASK ; 
 scalar_t__ MCP_TRACE_FORMAT_P1_SIZE_SHIFT ; 
 scalar_t__ MCP_TRACE_FORMAT_PARAM_WIDTH ; 
 scalar_t__ MFW_TRACE_ENTRY_SIZE ; 
 scalar_t__ MFW_TRACE_EVENTID_MASK ; 
 scalar_t__ MFW_TRACE_PRM_SIZE_MASK ; 
 scalar_t__ MFW_TRACE_PRM_SIZE_SHIFT ; 
 scalar_t__ qed_cyclic_add (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  qed_get_buf_ptr (char*,scalar_t__) ; 
 scalar_t__ qed_read_from_cyclic_buf (scalar_t__*,scalar_t__*,scalar_t__,scalar_t__) ; 
 char** s_mcp_trace_level_str ; 
 TYPE_1__ s_mcp_trace_meta ; 
 int /*<<< orphan*/  s_mcp_trace_meta_valid ; 
 scalar_t__ sprintf (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__,...) ; 

__attribute__((used)) static enum dbg_status qed_parse_mcp_trace_buf(u8 *trace_buf,
					       u32 trace_buf_size,
					       u32 data_offset,
					       u32 data_size,
					       char *parsed_buf,
					       u32 *parsed_bytes)
{
	u32 param_mask, param_shift;
	enum dbg_status status;

	*parsed_bytes = 0;

	if (!s_mcp_trace_meta_valid)
		return DBG_STATUS_MCP_TRACE_BAD_DATA;

	status = DBG_STATUS_OK;

	while (data_size) {
		struct mcp_trace_format *format_ptr;
		u8 format_level, format_module;
		u32 params[3] = { 0, 0, 0 };
		u32 header, format_idx, i;

		if (data_size < MFW_TRACE_ENTRY_SIZE)
			return DBG_STATUS_MCP_TRACE_BAD_DATA;

		header = qed_read_from_cyclic_buf(trace_buf,
						  &data_offset,
						  trace_buf_size,
						  MFW_TRACE_ENTRY_SIZE);
		data_size -= MFW_TRACE_ENTRY_SIZE;
		format_idx = header & MFW_TRACE_EVENTID_MASK;

		/* Skip message if its index doesn't exist in the meta data */
		if (format_idx >= s_mcp_trace_meta.formats_num) {
			u8 format_size =
				(u8)((header & MFW_TRACE_PRM_SIZE_MASK) >>
				     MFW_TRACE_PRM_SIZE_SHIFT);

			if (data_size < format_size)
				return DBG_STATUS_MCP_TRACE_BAD_DATA;

			data_offset = qed_cyclic_add(data_offset,
						     format_size,
						     trace_buf_size);
			data_size -= format_size;
			continue;
		}

		format_ptr = &s_mcp_trace_meta.formats[format_idx];

		for (i = 0,
		     param_mask = MCP_TRACE_FORMAT_P1_SIZE_MASK,
		     param_shift = MCP_TRACE_FORMAT_P1_SIZE_SHIFT;
		     i < MCP_TRACE_FORMAT_MAX_PARAMS;
		     i++,
		     param_mask <<= MCP_TRACE_FORMAT_PARAM_WIDTH,
		     param_shift += MCP_TRACE_FORMAT_PARAM_WIDTH) {
			/* Extract param size (0..3) */
			u8 param_size = (u8)((format_ptr->data & param_mask) >>
					     param_shift);

			/* If the param size is zero, there are no other
			 * parameters.
			 */
			if (!param_size)
				break;

			/* Size is encoded using 2 bits, where 3 is used to
			 * encode 4.
			 */
			if (param_size == 3)
				param_size = 4;

			if (data_size < param_size)
				return DBG_STATUS_MCP_TRACE_BAD_DATA;

			params[i] = qed_read_from_cyclic_buf(trace_buf,
							     &data_offset,
							     trace_buf_size,
							     param_size);
			data_size -= param_size;
		}

		format_level = (u8)((format_ptr->data &
				     MCP_TRACE_FORMAT_LEVEL_MASK) >>
				    MCP_TRACE_FORMAT_LEVEL_SHIFT);
		format_module = (u8)((format_ptr->data &
				      MCP_TRACE_FORMAT_MODULE_MASK) >>
				     MCP_TRACE_FORMAT_MODULE_SHIFT);
		if (format_level >= ARRAY_SIZE(s_mcp_trace_level_str))
			return DBG_STATUS_MCP_TRACE_BAD_DATA;

		/* Print current message to results buffer */
		*parsed_bytes +=
			sprintf(qed_get_buf_ptr(parsed_buf, *parsed_bytes),
				"%s %-8s: ",
				s_mcp_trace_level_str[format_level],
				s_mcp_trace_meta.modules[format_module]);
		*parsed_bytes +=
		    sprintf(qed_get_buf_ptr(parsed_buf, *parsed_bytes),
			    format_ptr->format_str,
			    params[0], params[1], params[2]);
	}

	/* Add string NULL terminator */
	(*parsed_bytes)++;

	return status;
}