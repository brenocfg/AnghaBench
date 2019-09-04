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
struct ioc3 {scalar_t__ eier; } ;
typedef  int /*<<< orphan*/  nasid_t ;
struct TYPE_2__ {scalar_t__ memory_base; } ;

/* Variables and functions */
 TYPE_1__* KL_CONFIG_CH_CONS_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_nasid () ; 

__attribute__((used)) static inline void ioc3_eth_init(void)
{
	struct ioc3 *ioc3;
	nasid_t nid;

	nid = get_nasid();
	ioc3 = (struct ioc3 *) KL_CONFIG_CH_CONS_INFO(nid)->memory_base;

	ioc3->eier = 0;
}