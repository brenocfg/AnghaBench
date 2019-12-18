#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct nouveau_cli {int dummy; } ;
struct TYPE_6__ {int num_pages; } ;
struct TYPE_8__ {TYPE_1__ mem; } ;
struct TYPE_9__ {int /*<<< orphan*/  virtual; } ;
struct nouveau_bo {int validate_mapped; TYPE_3__ bo; TYPE_5__ kmap; } ;
struct drm_nouveau_gem_pushbuf_reloc {size_t bo_index; size_t reloc_bo_index; int reloc_bo_offset; int flags; int data; int tor; int vor; } ;
struct TYPE_7__ {int offset; scalar_t__ domain; scalar_t__ valid; } ;
struct drm_nouveau_gem_pushbuf_bo {TYPE_2__ presumed; scalar_t__ user_priv; } ;
struct drm_nouveau_gem_pushbuf {unsigned int nr_relocs; size_t nr_buffers; int /*<<< orphan*/  relocs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ IS_ERR (struct drm_nouveau_gem_pushbuf_reloc*) ; 
 scalar_t__ NOUVEAU_GEM_DOMAIN_GART ; 
 int NOUVEAU_GEM_RELOC_HIGH ; 
 int NOUVEAU_GEM_RELOC_LOW ; 
 int NOUVEAU_GEM_RELOC_OR ; 
 int /*<<< orphan*/  NV_PRINTK (int /*<<< orphan*/ ,struct nouveau_cli*,char*,...) ; 
 int PAGE_SHIFT ; 
 int PTR_ERR (struct drm_nouveau_gem_pushbuf_reloc*) ; 
 int /*<<< orphan*/  err ; 
 int /*<<< orphan*/  nouveau_bo_wr32 (struct nouveau_bo*,int,int) ; 
 int ttm_bo_kmap (TYPE_3__*,int /*<<< orphan*/ ,int,TYPE_5__*) ; 
 int ttm_bo_wait (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  u_free (struct drm_nouveau_gem_pushbuf_reloc*) ; 
 struct drm_nouveau_gem_pushbuf_reloc* u_memcpya (int /*<<< orphan*/ ,unsigned int,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
nouveau_gem_pushbuf_reloc_apply(struct nouveau_cli *cli,
				struct drm_nouveau_gem_pushbuf *req,
				struct drm_nouveau_gem_pushbuf_bo *bo)
{
	struct drm_nouveau_gem_pushbuf_reloc *reloc = NULL;
	int ret = 0;
	unsigned i;

	reloc = u_memcpya(req->relocs, req->nr_relocs, sizeof(*reloc));
	if (IS_ERR(reloc))
		return PTR_ERR(reloc);

	for (i = 0; i < req->nr_relocs; i++) {
		struct drm_nouveau_gem_pushbuf_reloc *r = &reloc[i];
		struct drm_nouveau_gem_pushbuf_bo *b;
		struct nouveau_bo *nvbo;
		uint32_t data;

		if (unlikely(r->bo_index >= req->nr_buffers)) {
			NV_PRINTK(err, cli, "reloc bo index invalid\n");
			ret = -EINVAL;
			break;
		}

		b = &bo[r->bo_index];
		if (b->presumed.valid)
			continue;

		if (unlikely(r->reloc_bo_index >= req->nr_buffers)) {
			NV_PRINTK(err, cli, "reloc container bo index invalid\n");
			ret = -EINVAL;
			break;
		}
		nvbo = (void *)(unsigned long)bo[r->reloc_bo_index].user_priv;

		if (unlikely(r->reloc_bo_offset + 4 >
			     nvbo->bo.mem.num_pages << PAGE_SHIFT)) {
			NV_PRINTK(err, cli, "reloc outside of bo\n");
			ret = -EINVAL;
			break;
		}

		if (!nvbo->kmap.virtual) {
			ret = ttm_bo_kmap(&nvbo->bo, 0, nvbo->bo.mem.num_pages,
					  &nvbo->kmap);
			if (ret) {
				NV_PRINTK(err, cli, "failed kmap for reloc\n");
				break;
			}
			nvbo->validate_mapped = true;
		}

		if (r->flags & NOUVEAU_GEM_RELOC_LOW)
			data = b->presumed.offset + r->data;
		else
		if (r->flags & NOUVEAU_GEM_RELOC_HIGH)
			data = (b->presumed.offset + r->data) >> 32;
		else
			data = r->data;

		if (r->flags & NOUVEAU_GEM_RELOC_OR) {
			if (b->presumed.domain == NOUVEAU_GEM_DOMAIN_GART)
				data |= r->tor;
			else
				data |= r->vor;
		}

		ret = ttm_bo_wait(&nvbo->bo, false, false);
		if (ret) {
			NV_PRINTK(err, cli, "reloc wait_idle failed: %d\n", ret);
			break;
		}

		nouveau_bo_wr32(nvbo, r->reloc_bo_offset >> 2, data);
	}

	u_free(reloc);
	return ret;
}