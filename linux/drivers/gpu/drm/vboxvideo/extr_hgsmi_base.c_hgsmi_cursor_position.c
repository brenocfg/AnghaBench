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
typedef  void* u32 ;
struct vbva_cursor_position {int report_position; void* y; void* x; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  HGSMI_CH_VBVA ; 
 int /*<<< orphan*/  VBVA_CURSOR_POSITION ; 
 struct vbva_cursor_position* hgsmi_buffer_alloc (struct gen_pool*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hgsmi_buffer_free (struct gen_pool*,struct vbva_cursor_position*) ; 
 int /*<<< orphan*/  hgsmi_buffer_submit (struct gen_pool*,struct vbva_cursor_position*) ; 

int hgsmi_cursor_position(struct gen_pool *ctx, bool report_position,
			  u32 x, u32 y, u32 *x_host, u32 *y_host)
{
	struct vbva_cursor_position *p;

	p = hgsmi_buffer_alloc(ctx, sizeof(*p), HGSMI_CH_VBVA,
			       VBVA_CURSOR_POSITION);
	if (!p)
		return -ENOMEM;

	p->report_position = report_position;
	p->x = x;
	p->y = y;

	hgsmi_buffer_submit(ctx, p);

	*x_host = p->x;
	*y_host = p->y;

	hgsmi_buffer_free(ctx, p);

	return 0;
}