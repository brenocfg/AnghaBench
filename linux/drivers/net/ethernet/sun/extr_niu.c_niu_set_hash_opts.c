#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct niu {TYPE_1__* parent; } ;
struct ethtool_rxnfc {int data; int /*<<< orphan*/  flow_type; } ;
struct TYPE_2__ {scalar_t__* tcam_key; scalar_t__* flow_key; } ;

/* Variables and functions */
 scalar_t__ CLASS_CODE_SCTP_IPV6 ; 
 scalar_t__ CLASS_CODE_USER_PROG1 ; 
 int EINVAL ; 
 int /*<<< orphan*/  FLOW_KEY (scalar_t__) ; 
 int RXH_DISCARD ; 
 int /*<<< orphan*/  TCAM_KEY (scalar_t__) ; 
 scalar_t__ TCAM_KEY_DISC ; 
 int /*<<< orphan*/  niu_ethflow_to_class (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  niu_ethflow_to_flowkey (int,scalar_t__*) ; 
 int /*<<< orphan*/  niu_lock_parent (struct niu*,unsigned long) ; 
 int /*<<< orphan*/  niu_unlock_parent (struct niu*,unsigned long) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int niu_set_hash_opts(struct niu *np, struct ethtool_rxnfc *nfc)
{
	u64 class;
	u64 flow_key = 0;
	unsigned long flags;

	if (!niu_ethflow_to_class(nfc->flow_type, &class))
		return -EINVAL;

	if (class < CLASS_CODE_USER_PROG1 ||
	    class > CLASS_CODE_SCTP_IPV6)
		return -EINVAL;

	if (nfc->data & RXH_DISCARD) {
		niu_lock_parent(np, flags);
		flow_key = np->parent->tcam_key[class -
					       CLASS_CODE_USER_PROG1];
		flow_key |= TCAM_KEY_DISC;
		nw64(TCAM_KEY(class - CLASS_CODE_USER_PROG1), flow_key);
		np->parent->tcam_key[class - CLASS_CODE_USER_PROG1] = flow_key;
		niu_unlock_parent(np, flags);
		return 0;
	} else {
		/* Discard was set before, but is not set now */
		if (np->parent->tcam_key[class - CLASS_CODE_USER_PROG1] &
		    TCAM_KEY_DISC) {
			niu_lock_parent(np, flags);
			flow_key = np->parent->tcam_key[class -
					       CLASS_CODE_USER_PROG1];
			flow_key &= ~TCAM_KEY_DISC;
			nw64(TCAM_KEY(class - CLASS_CODE_USER_PROG1),
			     flow_key);
			np->parent->tcam_key[class - CLASS_CODE_USER_PROG1] =
				flow_key;
			niu_unlock_parent(np, flags);
		}
	}

	if (!niu_ethflow_to_flowkey(nfc->data, &flow_key))
		return -EINVAL;

	niu_lock_parent(np, flags);
	nw64(FLOW_KEY(class - CLASS_CODE_USER_PROG1), flow_key);
	np->parent->flow_key[class - CLASS_CODE_USER_PROG1] = flow_key;
	niu_unlock_parent(np, flags);

	return 0;
}