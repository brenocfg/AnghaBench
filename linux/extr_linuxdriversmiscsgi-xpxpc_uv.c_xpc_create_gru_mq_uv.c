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
struct xpc_gru_mq_uv {unsigned long order; struct xpc_gru_mq_uv* gru_mq_desc; scalar_t__ address; int /*<<< orphan*/  irq; int /*<<< orphan*/  mmr_value; int /*<<< orphan*/  mmr_blade; } ;
struct uv_IO_APIC_route_entry {int /*<<< orphan*/  dest; int /*<<< orphan*/  vector; } ;
struct page {int dummy; } ;
struct gru_message_queue_desc {int dummy; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;
typedef  enum xp_retval { ____Placeholder_xp_retval } xp_retval ;

/* Variables and functions */
 int EACCES ; 
 int EINVAL ; 
 int ENOMEM ; 
 struct xpc_gru_mq_uv* ERR_PTR (int) ; 
 int GFP_KERNEL ; 
 unsigned long PAGE_SHIFT ; 
 int UV_PNODE_TO_NASID (int /*<<< orphan*/ ) ; 
 int __GFP_THISNODE ; 
 int __GFP_ZERO ; 
 struct page* __alloc_pages_node (int,int,int) ; 
 int cpu_to_node (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_pages (unsigned long,int) ; 
 int get_order (unsigned int) ; 
 int gru_create_message_queue (struct xpc_gru_mq_uv*,scalar_t__,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct xpc_gru_mq_uv*) ; 
 struct xpc_gru_mq_uv* kmalloc (int,int) ; 
 struct xpc_gru_mq_uv* kzalloc (int,int) ; 
 scalar_t__ page_address (struct page*) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv_cpu_to_blade_id (int) ; 
 int /*<<< orphan*/  uv_cpu_to_pnode (int) ; 
 int xpSuccess ; 
 int xp_expand_memprotect (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  xp_pa (scalar_t__) ; 
 int xpc_get_gru_mq_irq_uv (struct xpc_gru_mq_uv*,int,char*) ; 
 int xpc_gru_mq_watchlist_alloc_uv (struct xpc_gru_mq_uv*) ; 
 int /*<<< orphan*/  xpc_gru_mq_watchlist_free_uv (struct xpc_gru_mq_uv*) ; 
 int /*<<< orphan*/  xpc_part ; 
 int /*<<< orphan*/  xpc_release_gru_mq_irq_uv (struct xpc_gru_mq_uv*) ; 

__attribute__((used)) static struct xpc_gru_mq_uv *
xpc_create_gru_mq_uv(unsigned int mq_size, int cpu, char *irq_name,
		     irq_handler_t irq_handler)
{
	enum xp_retval xp_ret;
	int ret;
	int nid;
	int nasid;
	int pg_order;
	struct page *page;
	struct xpc_gru_mq_uv *mq;
	struct uv_IO_APIC_route_entry *mmr_value;

	mq = kmalloc(sizeof(struct xpc_gru_mq_uv), GFP_KERNEL);
	if (mq == NULL) {
		dev_err(xpc_part, "xpc_create_gru_mq_uv() failed to kmalloc() "
			"a xpc_gru_mq_uv structure\n");
		ret = -ENOMEM;
		goto out_0;
	}

	mq->gru_mq_desc = kzalloc(sizeof(struct gru_message_queue_desc),
				  GFP_KERNEL);
	if (mq->gru_mq_desc == NULL) {
		dev_err(xpc_part, "xpc_create_gru_mq_uv() failed to kmalloc() "
			"a gru_message_queue_desc structure\n");
		ret = -ENOMEM;
		goto out_1;
	}

	pg_order = get_order(mq_size);
	mq->order = pg_order + PAGE_SHIFT;
	mq_size = 1UL << mq->order;

	mq->mmr_blade = uv_cpu_to_blade_id(cpu);

	nid = cpu_to_node(cpu);
	page = __alloc_pages_node(nid,
				      GFP_KERNEL | __GFP_ZERO | __GFP_THISNODE,
				      pg_order);
	if (page == NULL) {
		dev_err(xpc_part, "xpc_create_gru_mq_uv() failed to alloc %d "
			"bytes of memory on nid=%d for GRU mq\n", mq_size, nid);
		ret = -ENOMEM;
		goto out_2;
	}
	mq->address = page_address(page);

	/* enable generation of irq when GRU mq operation occurs to this mq */
	ret = xpc_gru_mq_watchlist_alloc_uv(mq);
	if (ret != 0)
		goto out_3;

	ret = xpc_get_gru_mq_irq_uv(mq, cpu, irq_name);
	if (ret != 0)
		goto out_4;

	ret = request_irq(mq->irq, irq_handler, 0, irq_name, NULL);
	if (ret != 0) {
		dev_err(xpc_part, "request_irq(irq=%d) returned error=%d\n",
			mq->irq, -ret);
		goto out_5;
	}

	nasid = UV_PNODE_TO_NASID(uv_cpu_to_pnode(cpu));

	mmr_value = (struct uv_IO_APIC_route_entry *)&mq->mmr_value;
	ret = gru_create_message_queue(mq->gru_mq_desc, mq->address, mq_size,
				     nasid, mmr_value->vector, mmr_value->dest);
	if (ret != 0) {
		dev_err(xpc_part, "gru_create_message_queue() returned "
			"error=%d\n", ret);
		ret = -EINVAL;
		goto out_6;
	}

	/* allow other partitions to access this GRU mq */
	xp_ret = xp_expand_memprotect(xp_pa(mq->address), mq_size);
	if (xp_ret != xpSuccess) {
		ret = -EACCES;
		goto out_6;
	}

	return mq;

	/* something went wrong */
out_6:
	free_irq(mq->irq, NULL);
out_5:
	xpc_release_gru_mq_irq_uv(mq);
out_4:
	xpc_gru_mq_watchlist_free_uv(mq);
out_3:
	free_pages((unsigned long)mq->address, pg_order);
out_2:
	kfree(mq->gru_mq_desc);
out_1:
	kfree(mq);
out_0:
	return ERR_PTR(ret);
}