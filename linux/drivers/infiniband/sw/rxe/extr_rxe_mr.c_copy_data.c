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
typedef  scalar_t__ u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct rxe_sge {int length; scalar_t__ addr; int /*<<< orphan*/  lkey; } ;
struct rxe_pd {int dummy; } ;
struct rxe_mem {int dummy; } ;
struct rxe_dma_info {size_t cur_sge; int sge_offset; int resid; size_t num_sge; struct rxe_sge* sge; } ;
typedef  enum copy_direction { ____Placeholder_copy_direction } copy_direction ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSPC ; 
 int /*<<< orphan*/  lookup_local ; 
 struct rxe_mem* lookup_mem (struct rxe_pd*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rxe_drop_ref (struct rxe_mem*) ; 
 int rxe_mem_copy (struct rxe_mem*,scalar_t__,void*,int,int,int /*<<< orphan*/ *) ; 

int copy_data(
	struct rxe_pd		*pd,
	int			access,
	struct rxe_dma_info	*dma,
	void			*addr,
	int			length,
	enum copy_direction	dir,
	u32			*crcp)
{
	int			bytes;
	struct rxe_sge		*sge	= &dma->sge[dma->cur_sge];
	int			offset	= dma->sge_offset;
	int			resid	= dma->resid;
	struct rxe_mem		*mem	= NULL;
	u64			iova;
	int			err;

	if (length == 0)
		return 0;

	if (length > resid) {
		err = -EINVAL;
		goto err2;
	}

	if (sge->length && (offset < sge->length)) {
		mem = lookup_mem(pd, access, sge->lkey, lookup_local);
		if (!mem) {
			err = -EINVAL;
			goto err1;
		}
	}

	while (length > 0) {
		bytes = length;

		if (offset >= sge->length) {
			if (mem) {
				rxe_drop_ref(mem);
				mem = NULL;
			}
			sge++;
			dma->cur_sge++;
			offset = 0;

			if (dma->cur_sge >= dma->num_sge) {
				err = -ENOSPC;
				goto err2;
			}

			if (sge->length) {
				mem = lookup_mem(pd, access, sge->lkey,
						 lookup_local);
				if (!mem) {
					err = -EINVAL;
					goto err1;
				}
			} else {
				continue;
			}
		}

		if (bytes > sge->length - offset)
			bytes = sge->length - offset;

		if (bytes > 0) {
			iova = sge->addr + offset;

			err = rxe_mem_copy(mem, iova, addr, bytes, dir, crcp);
			if (err)
				goto err2;

			offset	+= bytes;
			resid	-= bytes;
			length	-= bytes;
			addr	+= bytes;
		}
	}

	dma->sge_offset = offset;
	dma->resid	= resid;

	if (mem)
		rxe_drop_ref(mem);

	return 0;

err2:
	if (mem)
		rxe_drop_ref(mem);
err1:
	return err;
}