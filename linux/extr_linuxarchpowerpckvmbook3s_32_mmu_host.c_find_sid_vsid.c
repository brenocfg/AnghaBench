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
typedef  int /*<<< orphan*/  u64 ;
typedef  size_t u16 ;
struct kvmppc_sid_map {int /*<<< orphan*/  host_vsid; int /*<<< orphan*/  guest_vsid; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {struct kvmppc_sid_map* sid_map; } ;

/* Variables and functions */
 int MSR_PR ; 
 size_t SID_MAP_MASK ; 
 int /*<<< orphan*/  VSID_PR ; 
 int /*<<< orphan*/  dprintk_sr (char*,int /*<<< orphan*/ ,...) ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 size_t kvmppc_sid_hash (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 TYPE_1__* to_book3s (struct kvm_vcpu*) ; 

__attribute__((used)) static struct kvmppc_sid_map *find_sid_vsid(struct kvm_vcpu *vcpu, u64 gvsid)
{
	struct kvmppc_sid_map *map;
	u16 sid_map_mask;

	if (kvmppc_get_msr(vcpu) & MSR_PR)
		gvsid |= VSID_PR;

	sid_map_mask = kvmppc_sid_hash(vcpu, gvsid);
	map = &to_book3s(vcpu)->sid_map[sid_map_mask];
	if (map->guest_vsid == gvsid) {
		dprintk_sr("SR: Searching 0x%llx -> 0x%llx\n",
			    gvsid, map->host_vsid);
		return map;
	}

	map = &to_book3s(vcpu)->sid_map[SID_MAP_MASK - sid_map_mask];
	if (map->guest_vsid == gvsid) {
		dprintk_sr("SR: Searching 0x%llx -> 0x%llx\n",
			    gvsid, map->host_vsid);
		return map;
	}

	dprintk_sr("SR: Searching 0x%llx -> not found\n", gvsid);
	return NULL;
}