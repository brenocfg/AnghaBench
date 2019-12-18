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
typedef  enum dc_cursor_color_format { ____Placeholder_dc_cursor_color_format } dc_cursor_color_format ;
typedef  enum cursor_lines_per_chunk { ____Placeholder_cursor_lines_per_chunk } cursor_lines_per_chunk ;

/* Variables and functions */
 int CURSOR_LINE_PER_CHUNK_1 ; 
 int CURSOR_LINE_PER_CHUNK_16 ; 
 int CURSOR_LINE_PER_CHUNK_2 ; 
 int CURSOR_LINE_PER_CHUNK_4 ; 
 int CURSOR_LINE_PER_CHUNK_8 ; 
 int CURSOR_MODE_COLOR_1BIT_AND ; 
 int CURSOR_MODE_COLOR_64BIT_FP_PRE_MULTIPLIED ; 
 int CURSOR_MODE_COLOR_64BIT_FP_UN_PRE_MULTIPLIED ; 
 int CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA ; 
 int CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA ; 
 int CURSOR_MODE_MONO ; 

enum cursor_lines_per_chunk hubp2_get_lines_per_chunk(
	unsigned int cursor_width,
	enum dc_cursor_color_format cursor_mode)
{
	enum cursor_lines_per_chunk line_per_chunk = CURSOR_LINE_PER_CHUNK_16;

	if (cursor_mode == CURSOR_MODE_MONO)
		line_per_chunk = CURSOR_LINE_PER_CHUNK_16;
	else if (cursor_mode == CURSOR_MODE_COLOR_1BIT_AND ||
		 cursor_mode == CURSOR_MODE_COLOR_PRE_MULTIPLIED_ALPHA ||
		 cursor_mode == CURSOR_MODE_COLOR_UN_PRE_MULTIPLIED_ALPHA) {
		if (cursor_width >= 1   && cursor_width <= 32)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_16;
		else if (cursor_width >= 33  && cursor_width <= 64)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_8;
		else if (cursor_width >= 65  && cursor_width <= 128)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_4;
		else if (cursor_width >= 129 && cursor_width <= 256)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_2;
	} else if (cursor_mode == CURSOR_MODE_COLOR_64BIT_FP_PRE_MULTIPLIED ||
		   cursor_mode == CURSOR_MODE_COLOR_64BIT_FP_UN_PRE_MULTIPLIED) {
		if (cursor_width >= 1   && cursor_width <= 16)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_16;
		else if (cursor_width >= 17  && cursor_width <= 32)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_8;
		else if (cursor_width >= 33  && cursor_width <= 64)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_4;
		else if (cursor_width >= 65 && cursor_width <= 128)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_2;
		else if (cursor_width >= 129 && cursor_width <= 256)
			line_per_chunk = CURSOR_LINE_PER_CHUNK_1;
	}

	return line_per_chunk;
}