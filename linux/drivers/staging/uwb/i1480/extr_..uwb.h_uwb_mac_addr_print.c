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
struct uwb_mac_addr {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 size_t __uwb_addr_print (char*,size_t,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline size_t uwb_mac_addr_print(char *buf, size_t buf_size,
					const struct uwb_mac_addr *addr)
{
	return __uwb_addr_print(buf, buf_size, addr->data, 1);
}