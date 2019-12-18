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
struct nsim_bpf_bound_map {int /*<<< orphan*/  mutex; int /*<<< orphan*/  l; TYPE_1__* entry; } ;
struct bpf_offloaded_map {struct nsim_bpf_bound_map* dev_priv; } ;
struct TYPE_2__ {struct nsim_bpf_bound_map* value; struct nsim_bpf_bound_map* key; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct nsim_bpf_bound_map*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nsim_bpf_map_free(struct bpf_offloaded_map *offmap)
{
	struct nsim_bpf_bound_map *nmap = offmap->dev_priv;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(nmap->entry); i++) {
		kfree(nmap->entry[i].key);
		kfree(nmap->entry[i].value);
	}
	list_del_init(&nmap->l);
	mutex_destroy(&nmap->mutex);
	kfree(nmap);
}