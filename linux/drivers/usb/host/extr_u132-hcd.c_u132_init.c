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
typedef  int u32 ;
struct u132 {int num_ports; int /*<<< orphan*/  next_statechange; } ;
struct TYPE_2__ {int a; } ;

/* Variables and functions */
 int EINVAL ; 
 int MAX_U132_PORTS ; 
 int /*<<< orphan*/  OHCI_INTR_MIE ; 
 int RH_A_NDP ; 
 int /*<<< orphan*/  intrdisable ; 
 int /*<<< orphan*/  jiffies ; 
 int read_roothub_info (struct u132*) ; 
 TYPE_1__ roothub ; 
 int /*<<< orphan*/  u132_disable (struct u132*) ; 
 int u132_read_pcimem (struct u132*,int,int*) ; 
 int u132_write_pcimem (struct u132*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int u132_init(struct u132 *u132)
{
	int retval;
	u32 control;
	u132_disable(u132);
	u132->next_statechange = jiffies;
	retval = u132_write_pcimem(u132, intrdisable, OHCI_INTR_MIE);
	if (retval)
		return retval;
	retval = u132_read_pcimem(u132, control, &control);
	if (retval)
		return retval;
	if (u132->num_ports == 0) {
		u32 rh_a = -1;
		retval = u132_read_pcimem(u132, roothub.a, &rh_a);
		if (retval)
			return retval;
		u132->num_ports = rh_a & RH_A_NDP;
		retval = read_roothub_info(u132);
		if (retval)
			return retval;
	}
	if (u132->num_ports > MAX_U132_PORTS)
		return -EINVAL;

	return 0;
}