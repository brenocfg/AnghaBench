#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_8__ {int node_sz; } ;
struct mdesc_handle {TYPE_3__ mdesc; } ;
struct TYPE_6__ {int data_len; int /*<<< orphan*/  data_offset; } ;
struct TYPE_7__ {TYPE_1__ data; int /*<<< orphan*/  val; } ;
struct mdesc_elem {int tag; int name_offset; TYPE_2__ d; } ;

/* Variables and functions */
 scalar_t__ MDESC_NODE_NULL ; 
 int MD_NODE_END ; 
#define  MD_PROP_DATA 130 
#define  MD_PROP_STR 129 
#define  MD_PROP_VAL 128 
 void* data_block (TYPE_3__*) ; 
 char* name_block (TYPE_3__*) ; 
 struct mdesc_elem* node_block (TYPE_3__*) ; 
 int /*<<< orphan*/  strcmp (char const*,char const*) ; 

const void *mdesc_get_property(struct mdesc_handle *hp, u64 node,
			       const char *name, int *lenp)
{
	const char *names = name_block(&hp->mdesc);
	u64 last_node = hp->mdesc.node_sz / 16;
	void *data = data_block(&hp->mdesc);
	struct mdesc_elem *ep;

	if (node == MDESC_NODE_NULL || node >= last_node)
		return NULL;

	ep = node_block(&hp->mdesc) + node;
	ep++;
	for (; ep->tag != MD_NODE_END; ep++) {
		void *val = NULL;
		int len = 0;

		switch (ep->tag) {
		case MD_PROP_VAL:
			val = &ep->d.val;
			len = 8;
			break;

		case MD_PROP_STR:
		case MD_PROP_DATA:
			val = data + ep->d.data.data_offset;
			len = ep->d.data.data_len;
			break;

		default:
			break;
		}
		if (!val)
			continue;

		if (!strcmp(names + ep->name_offset, name)) {
			if (lenp)
				*lenp = len;
			return val;
		}
	}

	return NULL;
}