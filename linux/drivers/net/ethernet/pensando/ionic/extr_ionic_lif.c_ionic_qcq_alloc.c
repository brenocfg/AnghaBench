#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  uintptr_t u32 ;
struct TYPE_13__ {int index; int vector; int cpu; int /*<<< orphan*/  affinity_mask; } ;
struct TYPE_12__ {unsigned int type; void* info; } ;
struct TYPE_14__ {void* info; } ;
struct ionic_qcq {unsigned int flags; uintptr_t base_pa; uintptr_t total_size; TYPE_4__ intr; TYPE_1__ q; TYPE_5__ cq; void* base; } ;
struct ionic_lif {int /*<<< orphan*/  netdev; TYPE_10__* ionic; } ;
struct ionic_dev {int /*<<< orphan*/  intr_ctrl; } ;
struct device {int dummy; } ;
typedef  uintptr_t dma_addr_t ;
struct TYPE_11__ {struct device* dev; struct ionic_dev idev; } ;

/* Variables and functions */
 uintptr_t ALIGN (uintptr_t,uintptr_t) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int INTR_INDEX_NOT_ASSIGNED ; 
 int /*<<< orphan*/  IONIC_INTR_MASK_SET ; 
 unsigned int IONIC_QCQ_F_INTR ; 
 unsigned int IONIC_QCQ_F_SG ; 
 uintptr_t PAGE_SIZE ; 
 scalar_t__ cpu_online (int) ; 
 int /*<<< orphan*/  cpumask_set_cpu (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,char const*,unsigned int,int) ; 
 void* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 void* dma_alloc_coherent (struct device*,uintptr_t,uintptr_t*,int /*<<< orphan*/ ) ; 
 int ionic_bus_get_irq (TYPE_10__*,int) ; 
 int /*<<< orphan*/  ionic_cq_bind (TYPE_5__*,TYPE_1__*) ; 
 int ionic_cq_init (struct ionic_lif*,TYPE_5__*,TYPE_4__*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ionic_cq_map (TYPE_5__*,void*,uintptr_t) ; 
 int ionic_intr_alloc (struct ionic_lif*,TYPE_4__*) ; 
 int /*<<< orphan*/  ionic_intr_free (struct ionic_lif*,int) ; 
 int /*<<< orphan*/  ionic_intr_mask_assert (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ionic_q_init (struct ionic_lif*,struct ionic_dev*,TYPE_1__*,unsigned int,char const*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ionic_q_map (TYPE_1__*,void*,uintptr_t) ; 
 int /*<<< orphan*/  ionic_q_sg_map (TYPE_1__*,void*,uintptr_t) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int num_online_cpus () ; 

__attribute__((used)) static int ionic_qcq_alloc(struct ionic_lif *lif, unsigned int type,
			   unsigned int index,
			   const char *name, unsigned int flags,
			   unsigned int num_descs, unsigned int desc_size,
			   unsigned int cq_desc_size,
			   unsigned int sg_desc_size,
			   unsigned int pid, struct ionic_qcq **qcq)
{
	struct ionic_dev *idev = &lif->ionic->idev;
	u32 q_size, cq_size, sg_size, total_size;
	struct device *dev = lif->ionic->dev;
	void *q_base, *cq_base, *sg_base;
	dma_addr_t cq_base_pa = 0;
	dma_addr_t sg_base_pa = 0;
	dma_addr_t q_base_pa = 0;
	struct ionic_qcq *new;
	int err;

	*qcq = NULL;

	q_size  = num_descs * desc_size;
	cq_size = num_descs * cq_desc_size;
	sg_size = num_descs * sg_desc_size;

	total_size = ALIGN(q_size, PAGE_SIZE) + ALIGN(cq_size, PAGE_SIZE);
	/* Note: aligning q_size/cq_size is not enough due to cq_base
	 * address aligning as q_base could be not aligned to the page.
	 * Adding PAGE_SIZE.
	 */
	total_size += PAGE_SIZE;
	if (flags & IONIC_QCQ_F_SG) {
		total_size += ALIGN(sg_size, PAGE_SIZE);
		total_size += PAGE_SIZE;
	}

	new = devm_kzalloc(dev, sizeof(*new), GFP_KERNEL);
	if (!new) {
		netdev_err(lif->netdev, "Cannot allocate queue structure\n");
		err = -ENOMEM;
		goto err_out;
	}

	new->flags = flags;

	new->q.info = devm_kzalloc(dev, sizeof(*new->q.info) * num_descs,
				   GFP_KERNEL);
	if (!new->q.info) {
		netdev_err(lif->netdev, "Cannot allocate queue info\n");
		err = -ENOMEM;
		goto err_out;
	}

	new->q.type = type;

	err = ionic_q_init(lif, idev, &new->q, index, name, num_descs,
			   desc_size, sg_desc_size, pid);
	if (err) {
		netdev_err(lif->netdev, "Cannot initialize queue\n");
		goto err_out;
	}

	if (flags & IONIC_QCQ_F_INTR) {
		err = ionic_intr_alloc(lif, &new->intr);
		if (err) {
			netdev_warn(lif->netdev, "no intr for %s: %d\n",
				    name, err);
			goto err_out;
		}

		err = ionic_bus_get_irq(lif->ionic, new->intr.index);
		if (err < 0) {
			netdev_warn(lif->netdev, "no vector for %s: %d\n",
				    name, err);
			goto err_out_free_intr;
		}
		new->intr.vector = err;
		ionic_intr_mask_assert(idev->intr_ctrl, new->intr.index,
				       IONIC_INTR_MASK_SET);

		new->intr.cpu = new->intr.index % num_online_cpus();
		if (cpu_online(new->intr.cpu))
			cpumask_set_cpu(new->intr.cpu,
					&new->intr.affinity_mask);
	} else {
		new->intr.index = INTR_INDEX_NOT_ASSIGNED;
	}

	new->cq.info = devm_kzalloc(dev, sizeof(*new->cq.info) * num_descs,
				    GFP_KERNEL);
	if (!new->cq.info) {
		netdev_err(lif->netdev, "Cannot allocate completion queue info\n");
		err = -ENOMEM;
		goto err_out_free_intr;
	}

	err = ionic_cq_init(lif, &new->cq, &new->intr, num_descs, cq_desc_size);
	if (err) {
		netdev_err(lif->netdev, "Cannot initialize completion queue\n");
		goto err_out_free_intr;
	}

	new->base = dma_alloc_coherent(dev, total_size, &new->base_pa,
				       GFP_KERNEL);
	if (!new->base) {
		netdev_err(lif->netdev, "Cannot allocate queue DMA memory\n");
		err = -ENOMEM;
		goto err_out_free_intr;
	}

	new->total_size = total_size;

	q_base = new->base;
	q_base_pa = new->base_pa;

	cq_base = (void *)ALIGN((uintptr_t)q_base + q_size, PAGE_SIZE);
	cq_base_pa = ALIGN(q_base_pa + q_size, PAGE_SIZE);

	if (flags & IONIC_QCQ_F_SG) {
		sg_base = (void *)ALIGN((uintptr_t)cq_base + cq_size,
					PAGE_SIZE);
		sg_base_pa = ALIGN(cq_base_pa + cq_size, PAGE_SIZE);
		ionic_q_sg_map(&new->q, sg_base, sg_base_pa);
	}

	ionic_q_map(&new->q, q_base, q_base_pa);
	ionic_cq_map(&new->cq, cq_base, cq_base_pa);
	ionic_cq_bind(&new->cq, &new->q);

	*qcq = new;

	return 0;

err_out_free_intr:
	ionic_intr_free(lif, new->intr.index);
err_out:
	dev_err(dev, "qcq alloc of %s%d failed %d\n", name, index, err);
	return err;
}