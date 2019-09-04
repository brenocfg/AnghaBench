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
struct nfp_bpf_map {scalar_t__* use_map; } ;
struct bpf_verifier_env {int dummy; } ;
typedef  enum nfp_bpf_map_use { ____Placeholder_nfp_bpf_map_use } nfp_bpf_map_use ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ NFP_MAP_UNUSED ; 
 int /*<<< orphan*/  nfp_bpf_map_use_name (int) ; 
 int /*<<< orphan*/  pr_vlog (struct bpf_verifier_env*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int
nfp_bpf_map_mark_used_one(struct bpf_verifier_env *env,
			  struct nfp_bpf_map *nfp_map,
			  unsigned int off, enum nfp_bpf_map_use use)
{
	if (nfp_map->use_map[off / 4] != NFP_MAP_UNUSED &&
	    nfp_map->use_map[off / 4] != use) {
		pr_vlog(env, "map value use type conflict %s vs %s off: %u\n",
			nfp_bpf_map_use_name(nfp_map->use_map[off / 4]),
			nfp_bpf_map_use_name(use), off);
		return -EOPNOTSUPP;
	}

	nfp_map->use_map[off / 4] = use;

	return 0;
}