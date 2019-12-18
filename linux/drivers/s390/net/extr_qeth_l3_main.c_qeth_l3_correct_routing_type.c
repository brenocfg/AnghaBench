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
struct qeth_card {int dummy; } ;
typedef  enum qeth_routing_types { ____Placeholder_qeth_routing_types } qeth_routing_types ;
typedef  enum qeth_prot_versions { ____Placeholder_qeth_prot_versions } qeth_prot_versions ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IPA_OSA_MC_ROUTER ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
#define  MULTICAST_ROUTER 133 
#define  NO_ROUTER 132 
#define  PRIMARY_CONNECTOR 131 
#define  PRIMARY_ROUTER 130 
#define  SECONDARY_CONNECTOR 129 
#define  SECONDARY_ROUTER 128 
 int /*<<< orphan*/  qeth_is_ipafunc_supported (struct qeth_card*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_correct_routing_type(struct qeth_card *card,
		enum qeth_routing_types *type, enum qeth_prot_versions prot)
{
	if (IS_IQD(card)) {
		switch (*type) {
		case NO_ROUTER:
		case PRIMARY_CONNECTOR:
		case SECONDARY_CONNECTOR:
		case MULTICAST_ROUTER:
			return 0;
		default:
			goto out_inval;
		}
	} else {
		switch (*type) {
		case NO_ROUTER:
		case PRIMARY_ROUTER:
		case SECONDARY_ROUTER:
			return 0;
		case MULTICAST_ROUTER:
			if (qeth_is_ipafunc_supported(card, prot,
						      IPA_OSA_MC_ROUTER))
				return 0;
		default:
			goto out_inval;
		}
	}
out_inval:
	*type = NO_ROUTER;
	return -EINVAL;
}