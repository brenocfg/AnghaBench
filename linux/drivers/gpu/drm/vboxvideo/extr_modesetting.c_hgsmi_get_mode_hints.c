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
typedef  int /*<<< orphan*/  u8 ;
struct vbva_query_mode_hints {unsigned int hints_queried_count; int hint_structure_guest_size; scalar_t__ rc; } ;
struct vbva_modehint {int dummy; } ;
struct gen_pool {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  HGSMI_CH_VBVA ; 
 int /*<<< orphan*/  VBVA_QUERY_MODE_HINTS ; 
 scalar_t__ VERR_NOT_SUPPORTED ; 
 scalar_t__ WARN_ON (int) ; 
 struct vbva_query_mode_hints* hgsmi_buffer_alloc (struct gen_pool*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hgsmi_buffer_free (struct gen_pool*,struct vbva_query_mode_hints*) ; 
 int /*<<< orphan*/  hgsmi_buffer_submit (struct gen_pool*,struct vbva_query_mode_hints*) ; 
 int /*<<< orphan*/  memcpy (struct vbva_modehint*,int /*<<< orphan*/ *,size_t) ; 

int hgsmi_get_mode_hints(struct gen_pool *ctx, unsigned int screens,
			 struct vbva_modehint *hints)
{
	struct vbva_query_mode_hints *p;
	size_t size;

	if (WARN_ON(!hints))
		return -EINVAL;

	size = screens * sizeof(struct vbva_modehint);
	p = hgsmi_buffer_alloc(ctx, sizeof(*p) + size, HGSMI_CH_VBVA,
			       VBVA_QUERY_MODE_HINTS);
	if (!p)
		return -ENOMEM;

	p->hints_queried_count = screens;
	p->hint_structure_guest_size = sizeof(struct vbva_modehint);
	p->rc = VERR_NOT_SUPPORTED;

	hgsmi_buffer_submit(ctx, p);

	if (p->rc < 0) {
		hgsmi_buffer_free(ctx, p);
		return -EIO;
	}

	memcpy(hints, ((u8 *)p) + sizeof(struct vbva_query_mode_hints), size);
	hgsmi_buffer_free(ctx, p);

	return 0;
}