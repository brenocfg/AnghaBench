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
struct TYPE_6__ {unsigned int off; } ;
struct nfp_insn_meta {TYPE_3__ insn; } ;
struct nfp_bpf_map {int dummy; } ;
struct bpf_verifier_env {int dummy; } ;
struct TYPE_5__ {unsigned int value; } ;
struct bpf_reg_state {unsigned int off; int /*<<< orphan*/  map_ptr; TYPE_2__ var_off; } ;
struct TYPE_4__ {unsigned int value_size; } ;
struct bpf_offloaded_map {TYPE_1__ map; struct nfp_bpf_map* dev_priv; } ;
typedef  enum nfp_bpf_map_use { ____Placeholder_nfp_bpf_map_use } nfp_bpf_map_use ;

/* Variables and functions */
 unsigned int BPF_LDST_BYTES (TYPE_3__*) ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 struct bpf_offloaded_map* map_to_offmap (int /*<<< orphan*/ ) ; 
 int nfp_bpf_map_mark_used_one (struct bpf_verifier_env*,struct nfp_bpf_map*,unsigned int,int) ; 
 int /*<<< orphan*/  pr_vlog (struct bpf_verifier_env*,char*) ; 
 int /*<<< orphan*/  tnum_is_const (TYPE_2__) ; 

__attribute__((used)) static int
nfp_bpf_map_mark_used(struct bpf_verifier_env *env, struct nfp_insn_meta *meta,
		      const struct bpf_reg_state *reg,
		      enum nfp_bpf_map_use use)
{
	struct bpf_offloaded_map *offmap;
	struct nfp_bpf_map *nfp_map;
	unsigned int size, off;
	int i, err;

	if (!tnum_is_const(reg->var_off)) {
		pr_vlog(env, "map value offset is variable\n");
		return -EOPNOTSUPP;
	}

	off = reg->var_off.value + meta->insn.off + reg->off;
	size = BPF_LDST_BYTES(&meta->insn);
	offmap = map_to_offmap(reg->map_ptr);
	nfp_map = offmap->dev_priv;

	if (off + size > offmap->map.value_size) {
		pr_vlog(env, "map value access out-of-bounds\n");
		return -EINVAL;
	}

	for (i = 0; i < size; i += 4 - (off + i) % 4) {
		err = nfp_bpf_map_mark_used_one(env, nfp_map, off + i, use);
		if (err)
			return err;
	}

	return 0;
}