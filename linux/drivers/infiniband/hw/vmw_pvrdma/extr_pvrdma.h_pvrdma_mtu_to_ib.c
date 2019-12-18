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
typedef  enum pvrdma_mtu { ____Placeholder_pvrdma_mtu } pvrdma_mtu ;
typedef  enum ib_mtu { ____Placeholder_ib_mtu } ib_mtu ;

/* Variables and functions */

__attribute__((used)) static inline enum ib_mtu pvrdma_mtu_to_ib(enum pvrdma_mtu mtu)
{
	return (enum ib_mtu)mtu;
}