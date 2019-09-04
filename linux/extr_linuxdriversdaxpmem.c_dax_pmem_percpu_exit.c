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
struct percpu_ref {int dummy; } ;
struct dax_pmem {int /*<<< orphan*/  cmp; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  percpu_ref_exit (struct percpu_ref*) ; 
 struct dax_pmem* to_dax_pmem (struct percpu_ref*) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dax_pmem_percpu_exit(void *data)
{
	struct percpu_ref *ref = data;
	struct dax_pmem *dax_pmem = to_dax_pmem(ref);

	dev_dbg(dax_pmem->dev, "trace\n");
	wait_for_completion(&dax_pmem->cmp);
	percpu_ref_exit(ref);
}