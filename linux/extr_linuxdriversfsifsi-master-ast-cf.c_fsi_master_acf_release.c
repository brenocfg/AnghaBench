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
struct fsi_master_acf {int /*<<< orphan*/  dev; scalar_t__ sram; int /*<<< orphan*/  sram_pool; int /*<<< orphan*/  lock; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SRAM_SIZE ; 
 int /*<<< orphan*/  aspeed_gpio_copro_set_ops (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_of_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_to_fsi_master (struct device*) ; 
 int /*<<< orphan*/  fsi_master_acf_terminate (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  gen_pool_free (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct fsi_master_acf*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (int /*<<< orphan*/ ) ; 
 struct fsi_master_acf* to_fsi_master_acf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fsi_master_acf_release(struct device *dev)
{
	struct fsi_master_acf *master = to_fsi_master_acf(dev_to_fsi_master(dev));

	/* Cleanup, stop coprocessor */
	mutex_lock(&master->lock);
	fsi_master_acf_terminate(master);
	aspeed_gpio_copro_set_ops(NULL, NULL);
	mutex_unlock(&master->lock);

	/* Free resources */
	gen_pool_free(master->sram_pool, (unsigned long)master->sram, SRAM_SIZE);
	of_node_put(dev_of_node(master->dev));

	kfree(master);
}