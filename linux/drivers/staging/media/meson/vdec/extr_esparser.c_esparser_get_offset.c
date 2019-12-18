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
typedef  scalar_t__ u32 ;
struct amvdec_session {scalar_t__ vififo_paddr; scalar_t__ last_offset; int wrap_count; int vififo_size; struct amvdec_core* core; } ;
struct amvdec_core {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PARSER_VIDEO_WP ; 
 scalar_t__ amvdec_read_parser (struct amvdec_core*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u32 esparser_get_offset(struct amvdec_session *sess)
{
	struct amvdec_core *core = sess->core;
	u32 offset = amvdec_read_parser(core, PARSER_VIDEO_WP) -
		     sess->vififo_paddr;

	if (offset < sess->last_offset)
		sess->wrap_count++;

	sess->last_offset = offset;
	offset += (sess->wrap_count * sess->vififo_size);

	return offset;
}