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
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int QETH_PROT_IPV4 ; 
 int QETH_PROT_IPV6 ; 
 int /*<<< orphan*/  qeth_l3_ipaddr4_to_string (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  qeth_l3_ipaddr6_to_string (int /*<<< orphan*/  const*,char*) ; 

void qeth_l3_ipaddr_to_string(enum qeth_prot_versions proto, const __u8 *addr,
				char *buf)
{
	if (proto == QETH_PROT_IPV4)
		qeth_l3_ipaddr4_to_string(addr, buf);
	else if (proto == QETH_PROT_IPV6)
		qeth_l3_ipaddr6_to_string(addr, buf);
}