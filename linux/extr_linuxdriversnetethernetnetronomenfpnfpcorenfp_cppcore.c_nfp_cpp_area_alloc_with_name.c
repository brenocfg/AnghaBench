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
typedef  unsigned long long u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {unsigned long long start; unsigned long end; int /*<<< orphan*/  list; int /*<<< orphan*/  cpp_id; void* name; } ;
struct nfp_cpp_area {unsigned long long offset; unsigned long size; TYPE_2__ resource; int /*<<< orphan*/  mutex; int /*<<< orphan*/  kref; int /*<<< orphan*/  refcount; struct nfp_cpp* cpp; } ;
struct nfp_cpp {int /*<<< orphan*/  resource_lock; int /*<<< orphan*/  resource_list; TYPE_1__* op; int /*<<< orphan*/  imb_cat_table; } ;
struct TYPE_3__ {int area_priv_size; int (* area_init ) (struct nfp_cpp_area*,int /*<<< orphan*/ ,unsigned long long,unsigned long) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __resource_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct nfp_cpp_area*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct nfp_cpp_area* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nfp_target_cpp (int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ *,unsigned long long*,int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int stub1 (struct nfp_cpp_area*,int /*<<< orphan*/ ,unsigned long long,unsigned long) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

struct nfp_cpp_area *
nfp_cpp_area_alloc_with_name(struct nfp_cpp *cpp, u32 dest, const char *name,
			     unsigned long long address, unsigned long size)
{
	struct nfp_cpp_area *area;
	u64 tmp64 = address;
	int err, name_len;

	/* Remap from cpp_island to cpp_target */
	err = nfp_target_cpp(dest, tmp64, &dest, &tmp64, cpp->imb_cat_table);
	if (err < 0)
		return NULL;

	address = tmp64;

	if (!name)
		name = "(reserved)";

	name_len = strlen(name) + 1;
	area = kzalloc(sizeof(*area) + cpp->op->area_priv_size + name_len,
		       GFP_KERNEL);
	if (!area)
		return NULL;

	area->cpp = cpp;
	area->resource.name = (void *)area + sizeof(*area) +
		cpp->op->area_priv_size;
	memcpy((char *)area->resource.name, name, name_len);

	area->resource.cpp_id = dest;
	area->resource.start = address;
	area->resource.end = area->resource.start + size - 1;
	INIT_LIST_HEAD(&area->resource.list);

	atomic_set(&area->refcount, 0);
	kref_init(&area->kref);
	mutex_init(&area->mutex);

	if (cpp->op->area_init) {
		int err;

		err = cpp->op->area_init(area, dest, address, size);
		if (err < 0) {
			kfree(area);
			return NULL;
		}
	}

	write_lock(&cpp->resource_lock);
	__resource_add(&cpp->resource_list, &area->resource);
	write_unlock(&cpp->resource_lock);

	area->offset = address;
	area->size = size;

	return area;
}