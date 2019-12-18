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
struct whc_std {size_t len; size_t bounce_offset; struct scatterlist* bounce_sg; void* bounce_buf; } ;
struct whc {int dummy; } ;
struct scatterlist {size_t length; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (scalar_t__,void*,size_t) ; 
 size_t min (size_t,size_t) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 
 scalar_t__ sg_virt (struct scatterlist*) ; 

__attribute__((used)) static void qset_copy_bounce_to_sg(struct whc *whc, struct whc_std *std)
{
	struct scatterlist *sg;
	void *bounce;
	size_t remaining, offset;

	bounce = std->bounce_buf;
	remaining = std->len;

	sg = std->bounce_sg;
	offset = std->bounce_offset;

	while (remaining) {
		size_t len;

		len = min(sg->length - offset, remaining);
		memcpy(sg_virt(sg) + offset, bounce, len);

		bounce += len;
		remaining -= len;

		offset += len;
		if (offset >= sg->length) {
			sg = sg_next(sg);
			offset = 0;
		}
	}

}