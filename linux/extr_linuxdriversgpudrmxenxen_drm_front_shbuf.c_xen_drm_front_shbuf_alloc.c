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
struct xen_drm_front_shbuf_cfg {int /*<<< orphan*/  pages; int /*<<< orphan*/  size; int /*<<< orphan*/  xb_dev; scalar_t__ be_alloc; } ;
struct xen_drm_front_shbuf {TYPE_1__* ops; int /*<<< orphan*/  pages; int /*<<< orphan*/  num_pages; int /*<<< orphan*/  xb_dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* fill_page_dir ) (struct xen_drm_front_shbuf*) ;int /*<<< orphan*/  (* calc_num_grefs ) (struct xen_drm_front_shbuf*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DIV_ROUND_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 struct xen_drm_front_shbuf* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int alloc_storage (struct xen_drm_front_shbuf*) ; 
 TYPE_1__ backend_ops ; 
 int grant_references (struct xen_drm_front_shbuf*) ; 
 struct xen_drm_front_shbuf* kzalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ local_ops ; 
 int /*<<< orphan*/  stub1 (struct xen_drm_front_shbuf*) ; 
 int /*<<< orphan*/  stub2 (struct xen_drm_front_shbuf*) ; 
 int /*<<< orphan*/  xen_drm_front_shbuf_free (struct xen_drm_front_shbuf*) ; 

struct xen_drm_front_shbuf *
xen_drm_front_shbuf_alloc(struct xen_drm_front_shbuf_cfg *cfg)
{
	struct xen_drm_front_shbuf *buf;
	int ret;

	buf = kzalloc(sizeof(*buf), GFP_KERNEL);
	if (!buf)
		return ERR_PTR(-ENOMEM);

	if (cfg->be_alloc)
		buf->ops = &backend_ops;
	else
		buf->ops = &local_ops;

	buf->xb_dev = cfg->xb_dev;
	buf->num_pages = DIV_ROUND_UP(cfg->size, PAGE_SIZE);
	buf->pages = cfg->pages;

	buf->ops->calc_num_grefs(buf);

	ret = alloc_storage(buf);
	if (ret)
		goto fail;

	ret = grant_references(buf);
	if (ret)
		goto fail;

	buf->ops->fill_page_dir(buf);

	return buf;

fail:
	xen_drm_front_shbuf_free(buf);
	return ERR_PTR(ret);
}