#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct nvmet_ns {scalar_t__ blksize_shift; scalar_t__ size; int /*<<< orphan*/  bvec_pool; int /*<<< orphan*/  bvec_cache; TYPE_1__* file; int /*<<< orphan*/  device_path; int /*<<< orphan*/  buffered_io; } ;
struct kstat {scalar_t__ size; } ;
struct bio_vec {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_blkbits; } ;
struct TYPE_6__ {int /*<<< orphan*/  f_path; } ;

/* Variables and functions */
 int /*<<< orphan*/  AT_STATX_FORCE_SYNC ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int NVMET_MAX_MPOOL_BVEC ; 
 int /*<<< orphan*/  NVMET_MIN_MPOOL_OBJ ; 
 int O_DIRECT ; 
 int O_LARGEFILE ; 
 int O_RDWR ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  SLAB_HWCACHE_ALIGN ; 
 int /*<<< orphan*/  STATX_SIZE ; 
 TYPE_2__* file_inode (TYPE_1__*) ; 
 TYPE_1__* filp_open (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_create (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mempool_alloc_slab ; 
 int /*<<< orphan*/  mempool_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free_slab ; 
 scalar_t__ min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvmet_file_ns_disable (struct nvmet_ns*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u8 ; 
 int vfs_getattr (int /*<<< orphan*/ *,struct kstat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int nvmet_file_ns_enable(struct nvmet_ns *ns)
{
	int flags = O_RDWR | O_LARGEFILE;
	struct kstat stat;
	int ret;

	if (!ns->buffered_io)
		flags |= O_DIRECT;

	ns->file = filp_open(ns->device_path, flags, 0);
	if (IS_ERR(ns->file)) {
		pr_err("failed to open file %s: (%ld)\n",
				ns->device_path, PTR_ERR(ns->file));
		return PTR_ERR(ns->file);
	}

	ret = vfs_getattr(&ns->file->f_path,
			&stat, STATX_SIZE, AT_STATX_FORCE_SYNC);
	if (ret)
		goto err;

	ns->size = stat.size;
	/*
	 * i_blkbits can be greater than the universally accepted upper bound,
	 * so make sure we export a sane namespace lba_shift.
	 */
	ns->blksize_shift = min_t(u8,
			file_inode(ns->file)->i_blkbits, 12);

	ns->bvec_cache = kmem_cache_create("nvmet-bvec",
			NVMET_MAX_MPOOL_BVEC * sizeof(struct bio_vec),
			0, SLAB_HWCACHE_ALIGN, NULL);
	if (!ns->bvec_cache) {
		ret = -ENOMEM;
		goto err;
	}

	ns->bvec_pool = mempool_create(NVMET_MIN_MPOOL_OBJ, mempool_alloc_slab,
			mempool_free_slab, ns->bvec_cache);

	if (!ns->bvec_pool) {
		ret = -ENOMEM;
		goto err;
	}

	return ret;
err:
	ns->size = 0;
	ns->blksize_shift = 0;
	nvmet_file_ns_disable(ns);
	return ret;
}