#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ valid_ib_mtu (unsigned int) ; 

__attribute__((used)) static inline int valid_opa_max_mtu(unsigned int mtu)
{
	return mtu >= 2048 &&
		(valid_ib_mtu(mtu) || mtu == 8192 || mtu == 10240);
}