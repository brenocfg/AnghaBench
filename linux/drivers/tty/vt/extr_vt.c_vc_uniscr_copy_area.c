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
struct uni_screen {int /*<<< orphan*/ ** lines; } ;
typedef  int /*<<< orphan*/  char32_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  memset32 (int /*<<< orphan*/ *,char,unsigned int) ; 

__attribute__((used)) static void vc_uniscr_copy_area(struct uni_screen *dst,
				unsigned int dst_cols,
				unsigned int dst_rows,
				struct uni_screen *src,
				unsigned int src_cols,
				unsigned int src_top_row,
				unsigned int src_bot_row)
{
	unsigned int dst_row = 0;

	if (!dst)
		return;

	while (src_top_row < src_bot_row) {
		char32_t *src_line = src->lines[src_top_row];
		char32_t *dst_line = dst->lines[dst_row];

		memcpy(dst_line, src_line, src_cols * sizeof(char32_t));
		if (dst_cols - src_cols)
			memset32(dst_line + src_cols, ' ', dst_cols - src_cols);
		src_top_row++;
		dst_row++;
	}
	while (dst_row < dst_rows) {
		char32_t *dst_line = dst->lines[dst_row];

		memset32(dst_line, ' ', dst_cols);
		dst_row++;
	}
}