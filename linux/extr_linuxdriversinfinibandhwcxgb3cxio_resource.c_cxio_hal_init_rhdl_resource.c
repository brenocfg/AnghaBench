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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int cxio_init_resource_fifo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rhdl_fifo ; 
 int /*<<< orphan*/  rhdl_fifo_lock ; 

int cxio_hal_init_rhdl_resource(u32 nr_rhdl)
{
	return cxio_init_resource_fifo(&rhdl_fifo, &rhdl_fifo_lock, nr_rhdl, 1,
				       0);
}