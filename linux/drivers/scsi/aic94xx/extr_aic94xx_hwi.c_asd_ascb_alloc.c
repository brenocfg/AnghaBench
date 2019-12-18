#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct scb {int dummy; } ;
struct kmem_cache {int dummy; } ;
struct asd_seq_data {int /*<<< orphan*/  tc_index_lock; } ;
struct asd_ha_struct {int /*<<< orphan*/  scb_pool; struct asd_seq_data seq; } ;
struct TYPE_6__ {int size; int /*<<< orphan*/  dma_handle; int /*<<< orphan*/  vaddr; } ;
struct asd_ascb {int tc_index; TYPE_3__ dma_scb; TYPE_2__* scb; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_4__ {int /*<<< orphan*/  index; } ;
struct TYPE_5__ {TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASD_DPRINTK (char*) ; 
 int /*<<< orphan*/  asd_init_ascb (struct asd_ha_struct*,struct asd_ascb*) ; 
 int asd_tc_index_get (struct asd_seq_data*,struct asd_ascb*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_cache_free (struct kmem_cache*,struct asd_ascb*) ; 
 struct asd_ascb* kmem_cache_zalloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct asd_ascb *asd_ascb_alloc(struct asd_ha_struct *asd_ha,
				       gfp_t gfp_flags)
{
	extern struct kmem_cache *asd_ascb_cache;
	struct asd_seq_data *seq = &asd_ha->seq;
	struct asd_ascb *ascb;
	unsigned long flags;

	ascb = kmem_cache_zalloc(asd_ascb_cache, gfp_flags);

	if (ascb) {
		ascb->dma_scb.size = sizeof(struct scb);
		ascb->dma_scb.vaddr = dma_pool_zalloc(asd_ha->scb_pool,
						     gfp_flags,
						    &ascb->dma_scb.dma_handle);
		if (!ascb->dma_scb.vaddr) {
			kmem_cache_free(asd_ascb_cache, ascb);
			return NULL;
		}
		asd_init_ascb(asd_ha, ascb);

		spin_lock_irqsave(&seq->tc_index_lock, flags);
		ascb->tc_index = asd_tc_index_get(seq, ascb);
		spin_unlock_irqrestore(&seq->tc_index_lock, flags);
		if (ascb->tc_index == -1)
			goto undo;

		ascb->scb->header.index = cpu_to_le16((u16)ascb->tc_index);
	}

	return ascb;
undo:
	dma_pool_free(asd_ha->scb_pool, ascb->dma_scb.vaddr,
		      ascb->dma_scb.dma_handle);
	kmem_cache_free(asd_ascb_cache, ascb);
	ASD_DPRINTK("no index for ascb\n");
	return NULL;
}