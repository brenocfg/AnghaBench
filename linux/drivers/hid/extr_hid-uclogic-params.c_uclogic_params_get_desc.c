#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ desc_size; int /*<<< orphan*/ * desc_ptr; } ;
struct TYPE_3__ {scalar_t__ desc_size; int /*<<< orphan*/ * desc_ptr; } ;
struct uclogic_params {TYPE_2__ frame; TYPE_1__ pen; scalar_t__ desc_size; int /*<<< orphan*/ * desc_ptr; int /*<<< orphan*/  pen_unused; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/ * kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 

int uclogic_params_get_desc(const struct uclogic_params *params,
				__u8 **pdesc,
				unsigned int *psize)
{
	bool common_present;
	bool pen_present;
	bool frame_present;
	unsigned int size;
	__u8 *desc = NULL;

	/* Check arguments */
	if (params == NULL || pdesc == NULL || psize == NULL)
		return -EINVAL;

	size = 0;

	common_present = (params->desc_ptr != NULL);
	pen_present = (!params->pen_unused && params->pen.desc_ptr != NULL);
	frame_present = (params->frame.desc_ptr != NULL);

	if (common_present)
		size += params->desc_size;
	if (pen_present)
		size += params->pen.desc_size;
	if (frame_present)
		size += params->frame.desc_size;

	if (common_present || pen_present || frame_present) {
		__u8 *p;

		desc = kmalloc(size, GFP_KERNEL);
		if (desc == NULL)
			return -ENOMEM;
		p = desc;

		if (common_present) {
			memcpy(p, params->desc_ptr,
				params->desc_size);
			p += params->desc_size;
		}
		if (pen_present) {
			memcpy(p, params->pen.desc_ptr,
				params->pen.desc_size);
			p += params->pen.desc_size;
		}
		if (frame_present) {
			memcpy(p, params->frame.desc_ptr,
				params->frame.desc_size);
			p += params->frame.desc_size;
		}

		WARN_ON(p != desc + size);

		*psize = size;
	}

	*pdesc = desc;
	return 0;
}