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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct uverbs_attr_bundle {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED ; 
 int /*<<< orphan*/  IB_FLOW_ACTION_ESP_FLAGS_MOD_ESP_ATTRS ; 
 int /*<<< orphan*/  UVERBS_ATTR_FLOW_ACTION_ESP_ATTRS ; 
 int /*<<< orphan*/  UVERBS_ATTR_FLOW_ACTION_ESP_ESN ; 
 scalar_t__ uverbs_attr_is_valid (struct uverbs_attr_bundle*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 esp_flags_uverbs_to_verbs(struct uverbs_attr_bundle *attrs,
				     u32 flags, bool is_modify)
{
	u64 verbs_flags = flags;

	if (uverbs_attr_is_valid(attrs, UVERBS_ATTR_FLOW_ACTION_ESP_ESN))
		verbs_flags |= IB_FLOW_ACTION_ESP_FLAGS_ESN_TRIGGERED;

	if (is_modify && uverbs_attr_is_valid(attrs,
					      UVERBS_ATTR_FLOW_ACTION_ESP_ATTRS))
		verbs_flags |= IB_FLOW_ACTION_ESP_FLAGS_MOD_ESP_ATTRS;

	return verbs_flags;
}