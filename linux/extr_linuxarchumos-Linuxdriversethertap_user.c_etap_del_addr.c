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
struct ethertap_data {int control_fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  etap_close_addr (unsigned char*,unsigned char*,int*) ; 

__attribute__((used)) static void etap_del_addr(unsigned char *addr, unsigned char *netmask,
			  void *data)
{
	struct ethertap_data *pri = data;

	if (pri->control_fd == -1)
		return;

	etap_close_addr(addr, netmask, &pri->control_fd);
}