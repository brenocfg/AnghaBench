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
struct tc_cls_flower_offload {int /*<<< orphan*/  dissector; struct fl_flow_key* key; struct fl_flow_key* mask; } ;
struct flow_dissector_key_enc_opts {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct fl_flow_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLOW_DISSECTOR_KEY_ENC_OPTS ; 
 int /*<<< orphan*/  memcpy (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct flow_dissector_key_enc_opts* skb_flow_dissector_target (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fl_flow_key*) ; 

__attribute__((used)) static int
nfp_flower_compile_geneve_opt(void *key_buf, struct tc_cls_flower_offload *flow,
			      bool mask_version)
{
	struct fl_flow_key *target = mask_version ? flow->mask : flow->key;
	struct flow_dissector_key_enc_opts *opts;

	opts = skb_flow_dissector_target(flow->dissector,
					 FLOW_DISSECTOR_KEY_ENC_OPTS,
					 target);
	memcpy(key_buf, opts->data, opts->len);

	return 0;
}