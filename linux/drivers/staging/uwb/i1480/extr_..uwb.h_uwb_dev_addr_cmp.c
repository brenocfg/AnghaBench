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
struct uwb_dev_addr {int dummy; } ;

/* Variables and functions */
 int memcmp (struct uwb_dev_addr const*,struct uwb_dev_addr const*,int) ; 

__attribute__((used)) static inline int uwb_dev_addr_cmp(const struct uwb_dev_addr *addr1,
				   const struct uwb_dev_addr *addr2)
{
	return memcmp(addr1, addr2, sizeof(*addr1));
}