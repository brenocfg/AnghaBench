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
struct TYPE_2__ {int tblo; int tbhi; int crb; } ;
typedef  int /*<<< orphan*/  DEFINE_MUTEX ;

/* Variables and functions */
 int MS_TICKS ; 
 TYPE_1__ ciaa ; 
 int /*<<< orphan*/  ms_wait_completion ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ms_delay(int ms)
{
	int ticks;
	static DEFINE_MUTEX(mutex);

	if (ms > 0) {
		mutex_lock(&mutex);
		ticks = MS_TICKS*ms-1;
		ciaa.tblo=ticks%256;
		ciaa.tbhi=ticks/256;
		ciaa.crb=0x19; /*count eclock, force load, one-shoot, start */
		wait_for_completion(&ms_wait_completion);
		mutex_unlock(&mutex);
	}
}