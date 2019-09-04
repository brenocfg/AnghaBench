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
typedef  size_t u32 ;
struct ddb {TYPE_1__* port; } ;
struct TYPE_2__ {scalar_t__ output; scalar_t__* input; } ;

/* Variables and functions */
 size_t DDB_MAX_PORT ; 
 int /*<<< orphan*/  ddb_set_dma_table (scalar_t__) ; 

__attribute__((used)) static void ddb_set_dma_tables(struct ddb *dev)
{
	u32 i;

	for (i = 0; i < DDB_MAX_PORT; i++) {
		if (dev->port[i].input[0])
			ddb_set_dma_table(dev->port[i].input[0]);
		if (dev->port[i].input[1])
			ddb_set_dma_table(dev->port[i].input[1]);
		if (dev->port[i].output)
			ddb_set_dma_table(dev->port[i].output);
	}
}