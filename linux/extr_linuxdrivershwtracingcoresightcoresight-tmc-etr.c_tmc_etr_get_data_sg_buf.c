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
typedef  int /*<<< orphan*/  u64 ;
struct etr_sg_table {int /*<<< orphan*/  sg_table; } ;
struct etr_buf {struct etr_sg_table* private; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  tmc_sg_table_get_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t,char**) ; 

__attribute__((used)) static ssize_t tmc_etr_get_data_sg_buf(struct etr_buf *etr_buf, u64 offset,
				       size_t len, char **bufpp)
{
	struct etr_sg_table *etr_table = etr_buf->private;

	return tmc_sg_table_get_data(etr_table->sg_table, offset, len, bufpp);
}