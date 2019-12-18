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
struct uverbs_attr_bundle {int dummy; } ;
struct ib_uverbs_flow_action_esp_encap {scalar_t__ type; int /*<<< orphan*/  len; int /*<<< orphan*/  val_ptr; scalar_t__ next_ptr; } ;
struct ib_flow_spec_list {int /*<<< orphan*/  spec; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IB_FLOW_SPEC_IPV4 ; 
 scalar_t__ IB_FLOW_SPEC_IPV6 ; 
 int /*<<< orphan*/  UVERBS_ATTR_FLOW_ACTION_ESP_ENCAP ; 
 int parse_esp_ip (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  u64_to_user_ptr (int /*<<< orphan*/ ) ; 
 int uverbs_copy_from (struct ib_uverbs_flow_action_esp_encap*,struct uverbs_attr_bundle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int flow_action_esp_get_encap(struct ib_flow_spec_list *out,
				     struct uverbs_attr_bundle *attrs)
{
	struct ib_uverbs_flow_action_esp_encap uverbs_encap;
	int ret;

	ret = uverbs_copy_from(&uverbs_encap, attrs,
			       UVERBS_ATTR_FLOW_ACTION_ESP_ENCAP);
	if (ret)
		return ret;

	/* We currently support only one encap */
	if (uverbs_encap.next_ptr)
		return -EOPNOTSUPP;

	if (uverbs_encap.type != IB_FLOW_SPEC_IPV4 &&
	    uverbs_encap.type != IB_FLOW_SPEC_IPV6)
		return -EOPNOTSUPP;

	return parse_esp_ip(uverbs_encap.type,
			    u64_to_user_ptr(uverbs_encap.val_ptr),
			    uverbs_encap.len,
			    &out->spec);
}