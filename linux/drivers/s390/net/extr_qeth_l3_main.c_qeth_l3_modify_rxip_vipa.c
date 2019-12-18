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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; } ;
struct TYPE_6__ {TYPE_2__ a6; TYPE_1__ a4; } ;
struct qeth_ipaddr {TYPE_3__ u; } ;
struct qeth_card {int dummy; } ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;
typedef  enum qeth_ip_types { ____Placeholder_qeth_ip_types } qeth_ip_types ;

/* Variables and functions */
 int QETH_PROT_IPV4 ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  qeth_l3_init_ipaddr (struct qeth_ipaddr*,int,int) ; 
 int qeth_l3_modify_ip (struct qeth_card*,struct qeth_ipaddr*,int) ; 

int qeth_l3_modify_rxip_vipa(struct qeth_card *card, bool add, const u8 *ip,
			     enum qeth_ip_types type,
			     enum qeth_prot_versions proto)
{
	struct qeth_ipaddr addr;

	qeth_l3_init_ipaddr(&addr, type, proto);
	if (proto == QETH_PROT_IPV4)
		memcpy(&addr.u.a4.addr, ip, 4);
	else
		memcpy(&addr.u.a6.addr, ip, 16);

	return qeth_l3_modify_ip(card, &addr, add);
}