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
struct adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  setch_mutex; } ;

/* Variables and functions */
 TYPE_1__* adapter_to_dvobj (struct adapter*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_hal_set_chan (struct adapter*,unsigned char) ; 
 int /*<<< orphan*/  rtw_set_oper_ch (struct adapter*,unsigned char) ; 

void SelectChannel(struct adapter *padapter, unsigned char channel)
{
	if (mutex_lock_interruptible(&(adapter_to_dvobj(padapter)->setch_mutex)))
		return;

	/* saved channel info */
	rtw_set_oper_ch(padapter, channel);

	rtw_hal_set_chan(padapter, channel);

	mutex_unlock(&(adapter_to_dvobj(padapter)->setch_mutex));
}