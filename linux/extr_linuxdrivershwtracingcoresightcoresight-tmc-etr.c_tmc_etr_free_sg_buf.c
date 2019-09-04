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
struct etr_sg_table {int /*<<< orphan*/  sg_table; } ;
struct etr_buf {struct etr_sg_table* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct etr_sg_table*) ; 
 int /*<<< orphan*/  tmc_free_sg_table (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tmc_etr_free_sg_buf(struct etr_buf *etr_buf)
{
	struct etr_sg_table *etr_table = etr_buf->private;

	if (etr_table) {
		tmc_free_sg_table(etr_table->sg_table);
		kfree(etr_table);
	}
}