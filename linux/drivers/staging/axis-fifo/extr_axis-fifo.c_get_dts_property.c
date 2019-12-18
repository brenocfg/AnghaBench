#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct axis_fifo {TYPE_1__* dt_device; } ;
struct TYPE_3__ {int /*<<< orphan*/  of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (TYPE_1__*,char*,char*,unsigned int) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*,char*) ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,unsigned int*) ; 

__attribute__((used)) static int get_dts_property(struct axis_fifo *fifo,
			    char *name, unsigned int *var)
{
	int rc;

	rc = of_property_read_u32(fifo->dt_device->of_node, name, var);
	if (rc) {
		dev_err(fifo->dt_device, "couldn't read IP dts property '%s'",
			name);
		return rc;
	}
	dev_dbg(fifo->dt_device, "dts property '%s' = %u\n",
		name, *var);

	return 0;
}