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
typedef  size_t u32 ;
typedef  size_t u16 ;
struct qed_ooo_isle {int dummy; } ;
struct TYPE_4__ {size_t num_of_cqes; void* p_cqes; } ;
struct qed_ooo_info {size_t cid_base; size_t max_num_archipelagos; struct qed_ooo_info* p_isles_mem; struct qed_ooo_info* p_archipelagos_mem; TYPE_2__ ooo_history; int /*<<< orphan*/  isles_list; int /*<<< orphan*/  free_isles_list; int /*<<< orphan*/  list_entry; int /*<<< orphan*/  buffers_list; int /*<<< orphan*/  ready_buffers_list; int /*<<< orphan*/  free_buffers_list; } ;
struct qed_ooo_archipelago {int dummy; } ;
struct TYPE_3__ {int personality; } ;
struct qed_hwfn {struct qed_ooo_info* p_ooo_info; TYPE_1__ hw_info; } ;
struct ooo_opaque {int dummy; } ;
typedef  enum protocol_type { ____Placeholder_protocol_type } protocol_type ;

/* Variables and functions */
 int /*<<< orphan*/  DP_NOTICE (struct qed_hwfn*,char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int PROTOCOLID_ISCSI ; 
 int PROTOCOLID_IWARP ; 
 size_t QED_MAX_NUM_ISLES ; 
 size_t QED_MAX_NUM_OOO_HISTORY_ENTRIES ; 
#define  QED_PCI_ETH_IWARP 130 
#define  QED_PCI_ETH_RDMA 129 
#define  QED_PCI_ISCSI 128 
 void* kcalloc (size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qed_ooo_info*) ; 
 struct qed_ooo_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ qed_cxt_get_proto_cid_count (struct qed_hwfn*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ qed_cxt_get_proto_cid_start (struct qed_hwfn*,int) ; 

int qed_ooo_alloc(struct qed_hwfn *p_hwfn)
{
	u16 max_num_archipelagos = 0, cid_base;
	struct qed_ooo_info *p_ooo_info;
	enum protocol_type proto;
	u16 max_num_isles = 0;
	u32 i;

	switch (p_hwfn->hw_info.personality) {
	case QED_PCI_ISCSI:
		proto = PROTOCOLID_ISCSI;
		break;
	case QED_PCI_ETH_RDMA:
	case QED_PCI_ETH_IWARP:
		proto = PROTOCOLID_IWARP;
		break;
	default:
		DP_NOTICE(p_hwfn,
			  "Failed to allocate qed_ooo_info: unknown personality\n");
		return -EINVAL;
	}

	max_num_archipelagos = (u16)qed_cxt_get_proto_cid_count(p_hwfn, proto,
								NULL);
	max_num_isles = QED_MAX_NUM_ISLES + max_num_archipelagos;
	cid_base = (u16)qed_cxt_get_proto_cid_start(p_hwfn, proto);

	if (!max_num_archipelagos) {
		DP_NOTICE(p_hwfn,
			  "Failed to allocate qed_ooo_info: unknown amount of connections\n");
		return -EINVAL;
	}

	p_ooo_info = kzalloc(sizeof(*p_ooo_info), GFP_KERNEL);
	if (!p_ooo_info)
		return -ENOMEM;

	p_ooo_info->cid_base = cid_base;
	p_ooo_info->max_num_archipelagos = max_num_archipelagos;

	INIT_LIST_HEAD(&p_ooo_info->free_buffers_list);
	INIT_LIST_HEAD(&p_ooo_info->ready_buffers_list);
	INIT_LIST_HEAD(&p_ooo_info->free_isles_list);

	p_ooo_info->p_isles_mem = kcalloc(max_num_isles,
					  sizeof(struct qed_ooo_isle),
					  GFP_KERNEL);
	if (!p_ooo_info->p_isles_mem)
		goto no_isles_mem;

	for (i = 0; i < max_num_isles; i++) {
		INIT_LIST_HEAD(&p_ooo_info->p_isles_mem[i].buffers_list);
		list_add_tail(&p_ooo_info->p_isles_mem[i].list_entry,
			      &p_ooo_info->free_isles_list);
	}

	p_ooo_info->p_archipelagos_mem =
				kcalloc(max_num_archipelagos,
					sizeof(struct qed_ooo_archipelago),
					GFP_KERNEL);
	if (!p_ooo_info->p_archipelagos_mem)
		goto no_archipelagos_mem;

	for (i = 0; i < max_num_archipelagos; i++)
		INIT_LIST_HEAD(&p_ooo_info->p_archipelagos_mem[i].isles_list);

	p_ooo_info->ooo_history.p_cqes =
				kcalloc(QED_MAX_NUM_OOO_HISTORY_ENTRIES,
					sizeof(struct ooo_opaque),
					GFP_KERNEL);
	if (!p_ooo_info->ooo_history.p_cqes)
		goto no_history_mem;

	p_ooo_info->ooo_history.num_of_cqes = QED_MAX_NUM_OOO_HISTORY_ENTRIES;

	p_hwfn->p_ooo_info = p_ooo_info;
	return 0;

no_history_mem:
	kfree(p_ooo_info->p_archipelagos_mem);
no_archipelagos_mem:
	kfree(p_ooo_info->p_isles_mem);
no_isles_mem:
	kfree(p_ooo_info);
	return -ENOMEM;
}