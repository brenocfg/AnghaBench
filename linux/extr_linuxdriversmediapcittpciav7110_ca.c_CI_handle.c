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
typedef  int u8 ;
typedef  int u16 ;
struct av7110 {TYPE_1__* ci_slot; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CA_CI_MODULE_PRESENT ; 
 int /*<<< orphan*/  CA_CI_MODULE_READY ; 
#define  CI_MSG_CI_INFO 129 
#define  CI_SWITCH_PRG_REPLY 128 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 

void CI_handle(struct av7110 *av7110, u8 *data, u16 len)
{
	dprintk(8, "av7110:%p\n",av7110);

	if (len < 3)
		return;
	switch (data[0]) {
	case CI_MSG_CI_INFO:
		if (data[2] != 1 && data[2] != 2)
			break;
		switch (data[1]) {
		case 0:
			av7110->ci_slot[data[2] - 1].flags = 0;
			break;
		case 1:
			av7110->ci_slot[data[2] - 1].flags |= CA_CI_MODULE_PRESENT;
			break;
		case 2:
			av7110->ci_slot[data[2] - 1].flags |= CA_CI_MODULE_READY;
			break;
		}
		break;
	case CI_SWITCH_PRG_REPLY:
		//av7110->ci_stat=data[1];
		break;
	default:
		break;
	}
}