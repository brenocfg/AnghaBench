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
struct tuntap_data {int fd; int /*<<< orphan*/  dev_name; scalar_t__ fixed_config; } ;

/* Variables and functions */
 int /*<<< orphan*/  close_addr (unsigned char*,unsigned char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tuntap_del_addr(unsigned char *addr, unsigned char *netmask,
			    void *data)
{
	struct tuntap_data *pri = data;

	if ((pri->fd == -1) || pri->fixed_config)
		return;
	close_addr(addr, netmask, pri->dev_name);
}