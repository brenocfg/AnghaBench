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
struct sdb_component {int /*<<< orphan*/  addr_first; } ;
struct TYPE_4__ {int /*<<< orphan*/  sdb_child; struct sdb_component sdb_component; } ;
struct TYPE_3__ {scalar_t__ record_type; } ;
union sdb_record {int len; int level; unsigned long baseaddr; union sdb_record* parent; union sdb_record** subtree; TYPE_2__ bridge; TYPE_1__ empty; union sdb_record* record; struct fmc_device* fmc; } ;
typedef  unsigned long uint64_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct sdb_array {int len; int level; unsigned long baseaddr; struct sdb_array* parent; struct sdb_array** subtree; TYPE_2__ bridge; TYPE_1__ empty; struct sdb_array* record; struct fmc_device* fmc; } ;
struct fmc_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 union sdb_record* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (union sdb_record*) ; 
 scalar_t__ SDB_MAGIC ; 
 int __be16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ __be32_to_cpu (scalar_t__) ; 
 unsigned long __be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ __sdb_rd (struct fmc_device*,unsigned long,int) ; 
 scalar_t__ fmc_readl (struct fmc_device*,unsigned long) ; 
 void* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union sdb_record*) ; 
 union sdb_record* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ sdb_type_bridge ; 

__attribute__((used)) static struct sdb_array *__fmc_scan_sdb_tree(struct fmc_device *fmc,
					     unsigned long sdb_addr,
					     unsigned long reg_base, int level)
{
	uint32_t onew;
	int i, j, n, convert = 0;
	struct sdb_array *arr, *sub;

	onew = fmc_readl(fmc, sdb_addr);
	if (onew == SDB_MAGIC) {
		/* Uh! If we are little-endian, we must convert */
		if (SDB_MAGIC != __be32_to_cpu(SDB_MAGIC))
			convert = 1;
	} else if (onew == __be32_to_cpu(SDB_MAGIC)) {
		/* ok, don't convert */
	} else {
		return ERR_PTR(-ENOENT);
	}
	/* So, the magic was there: get the count from offset 4*/
	onew = __sdb_rd(fmc, sdb_addr + 4, convert);
	n = __be16_to_cpu(*(uint16_t *)&onew);
	arr = kzalloc(sizeof(*arr), GFP_KERNEL);
	if (!arr)
		return ERR_PTR(-ENOMEM);
	arr->record = kcalloc(n, sizeof(arr->record[0]), GFP_KERNEL);
	arr->subtree = kcalloc(n, sizeof(arr->subtree[0]), GFP_KERNEL);
	if (!arr->record || !arr->subtree) {
		kfree(arr->record);
		kfree(arr->subtree);
		kfree(arr);
		return ERR_PTR(-ENOMEM);
	}

	arr->len = n;
	arr->level = level;
	arr->fmc = fmc;
	for (i = 0; i < n; i++) {
		union  sdb_record *r;

		for (j = 0; j < sizeof(arr->record[0]); j += 4) {
			*(uint32_t *)((void *)(arr->record + i) + j) =
				__sdb_rd(fmc, sdb_addr + (i * 64) + j, convert);
		}
		r = &arr->record[i];
		arr->subtree[i] = ERR_PTR(-ENODEV);
		if (r->empty.record_type == sdb_type_bridge) {
			struct sdb_component *c = &r->bridge.sdb_component;
			uint64_t subaddr = __be64_to_cpu(r->bridge.sdb_child);
			uint64_t newbase = __be64_to_cpu(c->addr_first);

			subaddr += reg_base;
			newbase += reg_base;
			sub = __fmc_scan_sdb_tree(fmc, subaddr, newbase,
						  level + 1);
			arr->subtree[i] = sub; /* may be error */
			if (IS_ERR(sub))
				continue;
			sub->parent = arr;
			sub->baseaddr = newbase;
		}
	}
	return arr;
}