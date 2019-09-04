#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct cfv_info {int allocsz; int tx_hr; int tx_tr; int reserved_size; int watermark_tx; int /*<<< orphan*/  vq_tx; int /*<<< orphan*/  reserved_mem; int /*<<< orphan*/  genpool; TYPE_4__* ndev; scalar_t__ alloc_addr; int /*<<< orphan*/  alloc_dma; TYPE_3__* vdev; } ;
typedef  int /*<<< orphan*/  phys_addr_t ;
struct TYPE_9__ {int mtu; } ;
struct TYPE_7__ {TYPE_1__* parent; } ;
struct TYPE_8__ {TYPE_2__ dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  parent; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int ETH_DATA_LEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  cfv_destroy_genpool (struct cfv_info*) ; 
 scalar_t__ dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int gen_pool_add_virt (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gen_pool_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gen_pool_create (int,int) ; 
 int /*<<< orphan*/  netdev_dbg (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  netdev_info (TYPE_4__*,char*) ; 
 int num_possible_cpus () ; 
 scalar_t__ virt_to_phys (scalar_t__) ; 
 int virtqueue_get_vring_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cfv_create_genpool(struct cfv_info *cfv)
{
	int err;

	/* dma_alloc can only allocate whole pages, and we need a more
	 * fine graned allocation so we use genpool. We ask for space needed
	 * by IP and a full ring. If the dma allcoation fails we retry with a
	 * smaller allocation size.
	 */
	err = -ENOMEM;
	cfv->allocsz = (virtqueue_get_vring_size(cfv->vq_tx) *
			(ETH_DATA_LEN + cfv->tx_hr + cfv->tx_tr) * 11)/10;
	if (cfv->allocsz <= (num_possible_cpus() + 1) * cfv->ndev->mtu)
		return -EINVAL;

	for (;;) {
		if (cfv->allocsz <= num_possible_cpus() * cfv->ndev->mtu) {
			netdev_info(cfv->ndev, "Not enough device memory\n");
			return -ENOMEM;
		}

		cfv->alloc_addr = dma_alloc_coherent(
						cfv->vdev->dev.parent->parent,
						cfv->allocsz, &cfv->alloc_dma,
						GFP_ATOMIC);
		if (cfv->alloc_addr)
			break;

		cfv->allocsz = (cfv->allocsz * 3) >> 2;
	}

	netdev_dbg(cfv->ndev, "Allocated %zd bytes from dma-memory\n",
		   cfv->allocsz);

	/* Allocate on 128 bytes boundaries (1 << 7)*/
	cfv->genpool = gen_pool_create(7, -1);
	if (!cfv->genpool)
		goto err;

	err = gen_pool_add_virt(cfv->genpool, (unsigned long)cfv->alloc_addr,
				(phys_addr_t)virt_to_phys(cfv->alloc_addr),
				cfv->allocsz, -1);
	if (err)
		goto err;

	/* Reserve some memory for low memory situations. If we hit the roof
	 * in the memory pool, we stop TX flow and release the reserve.
	 */
	cfv->reserved_size = num_possible_cpus() * cfv->ndev->mtu;
	cfv->reserved_mem = gen_pool_alloc(cfv->genpool,
					   cfv->reserved_size);
	if (!cfv->reserved_mem) {
		err = -ENOMEM;
		goto err;
	}

	cfv->watermark_tx = virtqueue_get_vring_size(cfv->vq_tx);
	return 0;
err:
	cfv_destroy_genpool(cfv);
	return err;
}