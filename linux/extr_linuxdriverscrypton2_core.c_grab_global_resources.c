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
struct spu_queue {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NR_CPUS ; 
 int /*<<< orphan*/ * cpu_to_cwq ; 
 void* cpu_to_mau ; 
 int /*<<< orphan*/  global_ref ; 
 void* kcalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int n2_spu_hvapi_register () ; 
 int /*<<< orphan*/  n2_spu_hvapi_unregister () ; 
 int /*<<< orphan*/  queue_cache_destroy () ; 
 int queue_cache_init () ; 
 int /*<<< orphan*/  spu_lock ; 

__attribute__((used)) static int grab_global_resources(void)
{
	int err = 0;

	mutex_lock(&spu_lock);

	if (global_ref++)
		goto out;

	err = n2_spu_hvapi_register();
	if (err)
		goto out;

	err = queue_cache_init();
	if (err)
		goto out_hvapi_release;

	err = -ENOMEM;
	cpu_to_cwq = kcalloc(NR_CPUS, sizeof(struct spu_queue *),
			     GFP_KERNEL);
	if (!cpu_to_cwq)
		goto out_queue_cache_destroy;

	cpu_to_mau = kcalloc(NR_CPUS, sizeof(struct spu_queue *),
			     GFP_KERNEL);
	if (!cpu_to_mau)
		goto out_free_cwq_table;

	err = 0;

out:
	if (err)
		global_ref--;
	mutex_unlock(&spu_lock);
	return err;

out_free_cwq_table:
	kfree(cpu_to_cwq);
	cpu_to_cwq = NULL;

out_queue_cache_destroy:
	queue_cache_destroy();

out_hvapi_release:
	n2_spu_hvapi_unregister();
	goto out;
}