#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dpaa2_io_desc {size_t cpu; scalar_t__ receives_notifications; int /*<<< orphan*/  qman_version; int /*<<< orphan*/  regs_cinh; int /*<<< orphan*/  regs_cena; } ;
struct TYPE_2__ {int /*<<< orphan*/  qman_version; int /*<<< orphan*/  cinh_bar; int /*<<< orphan*/  cena_bar; } ;
struct dpaa2_io {struct device* dev; int /*<<< orphan*/  node; int /*<<< orphan*/  swp; struct dpaa2_io_desc dpio_desc; int /*<<< orphan*/  notifications; int /*<<< orphan*/  lock_notifications; int /*<<< orphan*/  lock_mgmt_cmd; TYPE_1__ swp_desc; } ;
struct device {int dummy; } ;

/* Variables and functions */
 size_t DPAA2_IO_ANY_CPU ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  QBMAN_SWP_INTERRUPT_DQRI ; 
 struct dpaa2_io** dpio_by_cpu ; 
 int /*<<< orphan*/  dpio_list ; 
 int /*<<< orphan*/  dpio_list_lock ; 
 int /*<<< orphan*/  kfree (struct dpaa2_io*) ; 
 struct dpaa2_io* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t num_possible_cpus () ; 
 int /*<<< orphan*/  qbman_swp_init (TYPE_1__*) ; 
 int /*<<< orphan*/  qbman_swp_interrupt_clear_status (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  qbman_swp_interrupt_set_trigger (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qbman_swp_push_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

struct dpaa2_io *dpaa2_io_create(const struct dpaa2_io_desc *desc,
				 struct device *dev)
{
	struct dpaa2_io *obj = kmalloc(sizeof(*obj), GFP_KERNEL);

	if (!obj)
		return NULL;

	/* check if CPU is out of range (-1 means any cpu) */
	if (desc->cpu != DPAA2_IO_ANY_CPU && desc->cpu >= num_possible_cpus()) {
		kfree(obj);
		return NULL;
	}

	obj->dpio_desc = *desc;
	obj->swp_desc.cena_bar = obj->dpio_desc.regs_cena;
	obj->swp_desc.cinh_bar = obj->dpio_desc.regs_cinh;
	obj->swp_desc.qman_version = obj->dpio_desc.qman_version;
	obj->swp = qbman_swp_init(&obj->swp_desc);

	if (!obj->swp) {
		kfree(obj);
		return NULL;
	}

	INIT_LIST_HEAD(&obj->node);
	spin_lock_init(&obj->lock_mgmt_cmd);
	spin_lock_init(&obj->lock_notifications);
	INIT_LIST_HEAD(&obj->notifications);

	/* For now only enable DQRR interrupts */
	qbman_swp_interrupt_set_trigger(obj->swp,
					QBMAN_SWP_INTERRUPT_DQRI);
	qbman_swp_interrupt_clear_status(obj->swp, 0xffffffff);
	if (obj->dpio_desc.receives_notifications)
		qbman_swp_push_set(obj->swp, 0, 1);

	spin_lock(&dpio_list_lock);
	list_add_tail(&obj->node, &dpio_list);
	if (desc->cpu >= 0 && !dpio_by_cpu[desc->cpu])
		dpio_by_cpu[desc->cpu] = obj;
	spin_unlock(&dpio_list_lock);

	obj->dev = dev;

	return obj;
}