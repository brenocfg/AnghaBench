#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ mask; } ;
struct TYPE_4__ {scalar_t__ pfxlen; } ;
struct TYPE_6__ {TYPE_2__ a4; TYPE_1__ a6; } ;
struct qeth_ipaddr {scalar_t__ type; scalar_t__ proto; TYPE_3__ u; } ;

/* Variables and functions */
 scalar_t__ QETH_PROT_IPV6 ; 

__attribute__((used)) static inline bool qeth_l3_addr_match_all(struct qeth_ipaddr *a1,
					  struct qeth_ipaddr *a2)
{
	/* Assumes that the pair was obtained via qeth_l3_addr_find_by_ip(),
	 * so 'proto' and 'addr' match for sure.
	 *
	 * For ucast:
	 * -	'mac' is always 0.
	 * -	'mask'/'pfxlen' for RXIP/VIPA is always 0. For NORMAL, matching
	 *	values are required to avoid mixups in takeover eligibility.
	 *
	 * For mcast,
	 * -	'mac' is mapped from the IP, and thus always matches.
	 * -	'mask'/'pfxlen' is always 0.
	 */
	if (a1->type != a2->type)
		return false;
	if (a1->proto == QETH_PROT_IPV6)
		return a1->u.a6.pfxlen == a2->u.a6.pfxlen;
	return a1->u.a4.mask == a2->u.a4.mask;
}