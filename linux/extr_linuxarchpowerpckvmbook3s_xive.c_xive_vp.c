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
typedef  scalar_t__ u32 ;
struct kvmppc_xive {int /*<<< orphan*/  kvm; scalar_t__ vp_base; } ;

/* Variables and functions */
 scalar_t__ kvmppc_pack_vcpu_id (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static u32 xive_vp(struct kvmppc_xive *xive, u32 server)
{
	return xive->vp_base + kvmppc_pack_vcpu_id(xive->kvm, server);
}