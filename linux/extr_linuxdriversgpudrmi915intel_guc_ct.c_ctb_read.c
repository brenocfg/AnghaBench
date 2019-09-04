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
typedef  size_t u32 ;
struct intel_guc_ct_buffer {size_t* cmds; struct guc_ct_buffer_desc* desc; } ;
struct guc_ct_buffer_desc {int head; int tail; int size; } ;
typedef  size_t s32 ;

/* Variables and functions */
 int /*<<< orphan*/  CT_DEBUG_DRIVER (char*,int,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int,size_t*,int,size_t*,int,size_t*) ; 
 int ENODATA ; 
 int EPROTO ; 
 int /*<<< orphan*/  GEM_BUG_ON (int) ; 
 int ct_header_get_len (size_t) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int ctb_read(struct intel_guc_ct_buffer *ctb, u32 *data)
{
	struct guc_ct_buffer_desc *desc = ctb->desc;
	u32 head = desc->head / 4;	/* in dwords */
	u32 tail = desc->tail / 4;	/* in dwords */
	u32 size = desc->size / 4;	/* in dwords */
	u32 *cmds = ctb->cmds;
	s32 available;			/* in dwords */
	unsigned int len;
	unsigned int i;

	GEM_BUG_ON(desc->size % 4);
	GEM_BUG_ON(desc->head % 4);
	GEM_BUG_ON(desc->tail % 4);
	GEM_BUG_ON(tail >= size);
	GEM_BUG_ON(head >= size);

	/* tail == head condition indicates empty */
	available = tail - head;
	if (unlikely(available == 0))
		return -ENODATA;

	/* beware of buffer wrap case */
	if (unlikely(available < 0))
		available += size;
	CT_DEBUG_DRIVER("CT: available %d (%u:%u)\n", available, head, tail);
	GEM_BUG_ON(available < 0);

	data[0] = cmds[head];
	head = (head + 1) % size;

	/* message len with header */
	len = ct_header_get_len(data[0]) + 1;
	if (unlikely(len > (u32)available)) {
		DRM_ERROR("CT: incomplete message %*ph %*ph %*ph\n",
			  4, data,
			  4 * (head + available - 1 > size ?
			       size - head : available - 1), &cmds[head],
			  4 * (head + available - 1 > size ?
			       available - 1 - size + head : 0), &cmds[0]);
		return -EPROTO;
	}

	for (i = 1; i < len; i++) {
		data[i] = cmds[head];
		head = (head + 1) % size;
	}
	CT_DEBUG_DRIVER("CT: received %*ph\n", 4 * len, data);

	desc->head = head * 4;
	return 0;
}