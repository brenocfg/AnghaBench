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
struct cobalt {TYPE_1__* i2c_adap; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int COBALT_NUM_ADAPTERS ; 
 int /*<<< orphan*/  cobalt_dbg (int,char*) ; 
 int /*<<< orphan*/  cobalt_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i2c_del_adapter (TYPE_1__*) ; 

void cobalt_i2c_exit(struct cobalt *cobalt)
{
	int i;

	cobalt_dbg(1, "i2c exit\n");

	for (i = 0; i < COBALT_NUM_ADAPTERS; i++) {
		cobalt_err("unregistered bus %s\n", cobalt->i2c_adap[i].name);
		i2c_del_adapter(&cobalt->i2c_adap[i]);
	}
}