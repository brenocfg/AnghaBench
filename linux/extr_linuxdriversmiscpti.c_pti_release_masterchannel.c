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
struct pti_masterchannel {int master; int channel; } ;
struct TYPE_2__ {int* ia_app; int* ia_os; int* ia_modem; } ;

/* Variables and functions */
 int APP_BASE_ID ; 
 int OS_BASE_ID ; 
 int /*<<< orphan*/  alloclock ; 
 TYPE_1__* drv_data ; 
 int /*<<< orphan*/  kfree (struct pti_masterchannel*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void pti_release_masterchannel(struct pti_masterchannel *mc)
{
	u8 master, channel, i;

	mutex_lock(&alloclock);

	if (mc) {
		master = mc->master;
		channel = mc->channel;

		if (master == APP_BASE_ID) {
			i = channel >> 3;
			drv_data->ia_app[i] &=  ~(0x80>>(channel & 0x7));
		} else if (master == OS_BASE_ID) {
			i = channel >> 3;
			drv_data->ia_os[i] &= ~(0x80>>(channel & 0x7));
		} else {
			i = channel >> 3;
			drv_data->ia_modem[i] &= ~(0x80>>(channel & 0x7));
		}

		kfree(mc);
	}

	mutex_unlock(&alloclock);
}