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
struct TYPE_3__ {int mtu; } ;

/* Variables and functions */
 int XMTU ; 
 TYPE_1__** arc_proto_map ; 
 TYPE_1__ arc_proto_null ; 

__attribute__((used)) static int choose_mtu(void)
{
	int count, mtu = 65535;

	/* choose the smallest MTU of all available encaps */
	for (count = 0; count < 256; count++) {
		if (arc_proto_map[count] != &arc_proto_null &&
		    arc_proto_map[count]->mtu < mtu) {
			mtu = arc_proto_map[count]->mtu;
		}
	}

	return mtu == 65535 ? XMTU : mtu;
}