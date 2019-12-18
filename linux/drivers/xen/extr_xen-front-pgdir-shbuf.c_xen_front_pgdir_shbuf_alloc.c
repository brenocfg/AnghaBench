#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xen_front_pgdir_shbuf_cfg {int /*<<< orphan*/  pages; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  xb_dev; scalar_t__ be_alloc; struct xen_front_pgdir_shbuf* pgdir; } ;
struct xen_front_pgdir_shbuf {TYPE_1__* ops; int /*<<< orphan*/  pages; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  xb_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fill_page_dir ) (struct xen_front_pgdir_shbuf*) ;int /*<<< orphan*/  (* calc_num_grefs ) (struct xen_front_pgdir_shbuf*) ;} ;

/* Variables and functions */
 int alloc_storage (struct xen_front_pgdir_shbuf*) ; 
 TYPE_1__ backend_ops ; 
 int grant_references (struct xen_front_pgdir_shbuf*) ; 
 TYPE_1__ local_ops ; 
 int /*<<< orphan*/  stub1 (struct xen_front_pgdir_shbuf*) ; 
 int /*<<< orphan*/  stub2 (struct xen_front_pgdir_shbuf*) ; 
 int /*<<< orphan*/  xen_front_pgdir_shbuf_free (struct xen_front_pgdir_shbuf*) ; 

int xen_front_pgdir_shbuf_alloc(struct xen_front_pgdir_shbuf_cfg *cfg)
{
	struct xen_front_pgdir_shbuf *buf = cfg->pgdir;
	int ret;

	if (cfg->be_alloc)
		buf->ops = &backend_ops;
	else
		buf->ops = &local_ops;
	buf->xb_dev = cfg->xb_dev;
	buf->num_pages = cfg->num_pages;
	buf->pages = cfg->pages;

	buf->ops->calc_num_grefs(buf);

	ret = alloc_storage(buf);
	if (ret)
		goto fail;

	ret = grant_references(buf);
	if (ret)
		goto fail;

	buf->ops->fill_page_dir(buf);

	return 0;

fail:
	xen_front_pgdir_shbuf_free(buf);
	return ret;
}