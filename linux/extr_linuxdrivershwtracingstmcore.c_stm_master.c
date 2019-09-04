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
struct stp_master {int dummy; } ;
struct stm_device {TYPE_1__* data; } ;
struct TYPE_2__ {unsigned int sw_start; unsigned int sw_end; } ;

/* Variables and functions */
 struct stp_master* __stm_master (struct stm_device*,unsigned int) ; 

__attribute__((used)) static inline struct stp_master *
stm_master(struct stm_device *stm, unsigned int idx)
{
	if (idx < stm->data->sw_start || idx > stm->data->sw_end)
		return NULL;

	return __stm_master(stm, idx);
}