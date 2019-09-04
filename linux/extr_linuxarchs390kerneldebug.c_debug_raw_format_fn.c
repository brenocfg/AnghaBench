#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct debug_view {int dummy; } ;
struct TYPE_3__ {int buf_size; } ;
typedef  TYPE_1__ debug_info_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 

__attribute__((used)) static int debug_raw_format_fn(debug_info_t *id, struct debug_view *view,
			       char *out_buf, const char *in_buf)
{
	int rc;

	rc = id->buf_size;
	memcpy(out_buf, in_buf, id->buf_size);
	return rc;
}