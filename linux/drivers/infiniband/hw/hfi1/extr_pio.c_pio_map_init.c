#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct send_context {int dummy; } ;
struct pio_vl_map {int actual_vls; int vls; int mask; int /*<<< orphan*/  list; TYPE_2__** map; } ;
struct pio_map_elem {int dummy; } ;
struct hfi1_devdata {int num_send_contexts; int /*<<< orphan*/  pio_map_lock; int /*<<< orphan*/  pio_map; scalar_t__* kernel_send_context; TYPE_1__* send_contexts; } ;
struct TYPE_4__ {int mask; scalar_t__* ksc; } ;
struct TYPE_3__ {scalar_t__ type; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int OPA_MAX_VLS ; 
 scalar_t__ SC_KERNEL ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ilog2 (int) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pio_map_free (struct pio_vl_map*) ; 
 int /*<<< orphan*/  pio_map_rcu_callback ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,struct pio_vl_map*) ; 
 struct pio_vl_map* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int roundup_pow_of_two (int) ; 
 int /*<<< orphan*/  set_threshold (struct hfi1_devdata*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int pio_map_init(struct hfi1_devdata *dd, u8 port, u8 num_vls, u8 *vl_scontexts)
{
	int i, j;
	int extra, sc_per_vl;
	int scontext = 1;
	int num_kernel_send_contexts = 0;
	u8 lvl_scontexts[OPA_MAX_VLS];
	struct pio_vl_map *oldmap, *newmap;

	if (!vl_scontexts) {
		for (i = 0; i < dd->num_send_contexts; i++)
			if (dd->send_contexts[i].type == SC_KERNEL)
				num_kernel_send_contexts++;
		/* truncate divide */
		sc_per_vl = num_kernel_send_contexts / num_vls;
		/* extras */
		extra = num_kernel_send_contexts % num_vls;
		vl_scontexts = lvl_scontexts;
		/* add extras from last vl down */
		for (i = num_vls - 1; i >= 0; i--, extra--)
			vl_scontexts[i] = sc_per_vl + (extra > 0 ? 1 : 0);
	}
	/* build new map */
	newmap = kzalloc(sizeof(*newmap) +
			 roundup_pow_of_two(num_vls) *
			 sizeof(struct pio_map_elem *),
			 GFP_KERNEL);
	if (!newmap)
		goto bail;
	newmap->actual_vls = num_vls;
	newmap->vls = roundup_pow_of_two(num_vls);
	newmap->mask = (1 << ilog2(newmap->vls)) - 1;
	for (i = 0; i < newmap->vls; i++) {
		/* save for wrap around */
		int first_scontext = scontext;

		if (i < newmap->actual_vls) {
			int sz = roundup_pow_of_two(vl_scontexts[i]);

			/* only allocate once */
			newmap->map[i] = kzalloc(sizeof(*newmap->map[i]) +
						 sz * sizeof(struct
							     send_context *),
						 GFP_KERNEL);
			if (!newmap->map[i])
				goto bail;
			newmap->map[i]->mask = (1 << ilog2(sz)) - 1;
			/*
			 * assign send contexts and
			 * adjust credit return threshold
			 */
			for (j = 0; j < sz; j++) {
				if (dd->kernel_send_context[scontext]) {
					newmap->map[i]->ksc[j] =
					dd->kernel_send_context[scontext];
					set_threshold(dd, scontext, i);
				}
				if (++scontext >= first_scontext +
						  vl_scontexts[i])
					/* wrap back to first send context */
					scontext = first_scontext;
			}
		} else {
			/* just re-use entry without allocating */
			newmap->map[i] = newmap->map[i % num_vls];
		}
		scontext = first_scontext + vl_scontexts[i];
	}
	/* newmap in hand, save old map */
	spin_lock_irq(&dd->pio_map_lock);
	oldmap = rcu_dereference_protected(dd->pio_map,
					   lockdep_is_held(&dd->pio_map_lock));

	/* publish newmap */
	rcu_assign_pointer(dd->pio_map, newmap);

	spin_unlock_irq(&dd->pio_map_lock);
	/* success, free any old map after grace period */
	if (oldmap)
		call_rcu(&oldmap->list, pio_map_rcu_callback);
	return 0;
bail:
	/* free any partial allocation */
	pio_map_free(newmap);
	return -ENOMEM;
}