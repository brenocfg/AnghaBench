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
struct fddi_addr {int* a; } ;

/* Variables and functions */
 int GROUP_ADDR ; 

__attribute__((used)) static inline int is_individual(const struct fddi_addr *addr)
{
	return !(addr->a[0] & GROUP_ADDR);
}