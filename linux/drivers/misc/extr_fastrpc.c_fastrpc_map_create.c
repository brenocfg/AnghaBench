#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct fastrpc_user {int /*<<< orphan*/  lock; int /*<<< orphan*/  maps; struct fastrpc_session_ctx* sctx; } ;
struct fastrpc_session_ctx {scalar_t__ sid; int /*<<< orphan*/  dev; } ;
struct fastrpc_map {int fd; int phys; int size; int len; TYPE_1__* buf; TYPE_1__* attach; int /*<<< orphan*/  node; int /*<<< orphan*/  refcount; TYPE_1__* table; int /*<<< orphan*/  va; struct fastrpc_user* fl; } ;
struct TYPE_11__ {int /*<<< orphan*/  sgl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_ERR (TYPE_1__*) ; 
 int PTR_ERR (TYPE_1__*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* dma_buf_attach (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_detach (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* dma_buf_get (int) ; 
 TYPE_1__* dma_buf_map_attachment (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_buf_put (TYPE_1__*) ; 
 int /*<<< orphan*/  fastrpc_map_find (struct fastrpc_user*,int,struct fastrpc_map**) ; 
 int /*<<< orphan*/  kfree (struct fastrpc_map*) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 struct fastrpc_map* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sg_dma_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_virt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fastrpc_map_create(struct fastrpc_user *fl, int fd,
			      u64 len, struct fastrpc_map **ppmap)
{
	struct fastrpc_session_ctx *sess = fl->sctx;
	struct fastrpc_map *map = NULL;
	int err = 0;

	if (!fastrpc_map_find(fl, fd, ppmap))
		return 0;

	map = kzalloc(sizeof(*map), GFP_KERNEL);
	if (!map)
		return -ENOMEM;

	INIT_LIST_HEAD(&map->node);
	map->fl = fl;
	map->fd = fd;
	map->buf = dma_buf_get(fd);
	if (IS_ERR(map->buf)) {
		err = PTR_ERR(map->buf);
		goto get_err;
	}

	map->attach = dma_buf_attach(map->buf, sess->dev);
	if (IS_ERR(map->attach)) {
		dev_err(sess->dev, "Failed to attach dmabuf\n");
		err = PTR_ERR(map->attach);
		goto attach_err;
	}

	map->table = dma_buf_map_attachment(map->attach, DMA_BIDIRECTIONAL);
	if (IS_ERR(map->table)) {
		err = PTR_ERR(map->table);
		goto map_err;
	}

	map->phys = sg_dma_address(map->table->sgl);
	map->phys += ((u64)fl->sctx->sid << 32);
	map->size = len;
	map->va = sg_virt(map->table->sgl);
	map->len = len;
	kref_init(&map->refcount);

	spin_lock(&fl->lock);
	list_add_tail(&map->node, &fl->maps);
	spin_unlock(&fl->lock);
	*ppmap = map;

	return 0;

map_err:
	dma_buf_detach(map->buf, map->attach);
attach_err:
	dma_buf_put(map->buf);
get_err:
	kfree(map);

	return err;
}