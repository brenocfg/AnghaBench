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
struct sockaddr_in6 {int dummy; } ;
struct rdma_dev_addr {int dummy; } ;
struct dst_entry {int dummy; } ;

/* Variables and functions */
 int EADDRNOTAVAIL ; 

__attribute__((used)) static int addr6_resolve(struct sockaddr_in6 *src_in,
			 const struct sockaddr_in6 *dst_in,
			 struct rdma_dev_addr *addr,
			 struct dst_entry **pdst)
{
	return -EADDRNOTAVAIL;
}