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
typedef  size_t u16 ;
struct kvmppc_vcpu_book3s {scalar_t__ proto_vsid_next; scalar_t__ proto_vsid_max; scalar_t__ proto_vsid_first; struct kvmppc_sid_map* sid_map; } ;
struct kvmppc_sid_map {int valid; int /*<<< orphan*/  host_vsid; int /*<<< orphan*/  guest_vsid; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_FTR_68_BIT_VA ; 
 int MSR_PR ; 
 size_t SID_MAP_MASK ; 
 int SID_MAP_NUM ; 
 unsigned long VSID_BITS_256M ; 
 unsigned long VSID_BITS_65_256M ; 
 int /*<<< orphan*/  VSID_MULTIPLIER_256M ; 
 int /*<<< orphan*/  VSID_PR ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_flush_segments (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_pte_flush (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t kvmppc_sid_hash (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct kvmppc_sid_map*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mmu_has_feature (int /*<<< orphan*/ ) ; 
 struct kvmppc_vcpu_book3s* to_book3s (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  trace_kvm_book3s_slb_map (size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vsid_scramble (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static struct kvmppc_sid_map *create_sid_map(struct kvm_vcpu *vcpu, u64 gvsid)
{
	unsigned long vsid_bits = VSID_BITS_65_256M;
	struct kvmppc_sid_map *map;
	struct kvmppc_vcpu_book3s *vcpu_book3s = to_book3s(vcpu);
	u16 sid_map_mask;
	static int backwards_map = 0;

	if (kvmppc_get_msr(vcpu) & MSR_PR)
		gvsid |= VSID_PR;

	/* We might get collisions that trap in preceding order, so let's
	   map them differently */

	sid_map_mask = kvmppc_sid_hash(vcpu, gvsid);
	if (backwards_map)
		sid_map_mask = SID_MAP_MASK - sid_map_mask;

	map = &to_book3s(vcpu)->sid_map[sid_map_mask];

	/* Make sure we're taking the other map next time */
	backwards_map = !backwards_map;

	/* Uh-oh ... out of mappings. Let's flush! */
	if (vcpu_book3s->proto_vsid_next == vcpu_book3s->proto_vsid_max) {
		vcpu_book3s->proto_vsid_next = vcpu_book3s->proto_vsid_first;
		memset(vcpu_book3s->sid_map, 0,
		       sizeof(struct kvmppc_sid_map) * SID_MAP_NUM);
		kvmppc_mmu_pte_flush(vcpu, 0, 0);
		kvmppc_mmu_flush_segments(vcpu);
	}

	if (mmu_has_feature(MMU_FTR_68_BIT_VA))
		vsid_bits = VSID_BITS_256M;

	map->host_vsid = vsid_scramble(vcpu_book3s->proto_vsid_next++,
				       VSID_MULTIPLIER_256M, vsid_bits);

	map->guest_vsid = gvsid;
	map->valid = true;

	trace_kvm_book3s_slb_map(sid_map_mask, gvsid, map->host_vsid);

	return map;
}