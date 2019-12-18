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
typedef  int /*<<< orphan*/  u32 ;
struct qeth_ipaddr {int type; int /*<<< orphan*/  ipato; } ;

/* Variables and functions */
 int /*<<< orphan*/  QETH_IPA_DELIP_VIPA_FLAG ; 
 int /*<<< orphan*/  QETH_IPA_SETIP_TAKEOVER_FLAG ; 
 int /*<<< orphan*/  QETH_IPA_SETIP_VIPA_FLAG ; 
#define  QETH_IP_TYPE_RXIP 129 
#define  QETH_IP_TYPE_VIPA 128 

__attribute__((used)) static u32 qeth_l3_get_setdelip_flags(struct qeth_ipaddr *addr, bool set)
{
	switch (addr->type) {
	case QETH_IP_TYPE_RXIP:
		return (set) ? QETH_IPA_SETIP_TAKEOVER_FLAG : 0;
	case QETH_IP_TYPE_VIPA:
		return (set) ? QETH_IPA_SETIP_VIPA_FLAG :
			       QETH_IPA_DELIP_VIPA_FLAG;
	default:
		return (set && addr->ipato) ? QETH_IPA_SETIP_TAKEOVER_FLAG : 0;
	}
}