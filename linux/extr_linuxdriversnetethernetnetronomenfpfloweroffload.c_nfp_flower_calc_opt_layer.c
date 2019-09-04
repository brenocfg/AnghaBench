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
struct nfp_flower_geneve_options {int dummy; } ;
struct flow_dissector_key_enc_opts {scalar_t__ len; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  NFP_FLOWER_LAYER2_GENEVE_OP ; 
 scalar_t__ NFP_FL_MAX_GENEVE_OPT_KEY ; 

__attribute__((used)) static int
nfp_flower_calc_opt_layer(struct flow_dissector_key_enc_opts *enc_opts,
			  u32 *key_layer_two, int *key_size)
{
	if (enc_opts->len > NFP_FL_MAX_GENEVE_OPT_KEY)
		return -EOPNOTSUPP;

	if (enc_opts->len > 0) {
		*key_layer_two |= NFP_FLOWER_LAYER2_GENEVE_OP;
		*key_size += sizeof(struct nfp_flower_geneve_options);
	}

	return 0;
}