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
typedef  int ulong ;
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_HCALL_TOKEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KVM_HC_PPC_MAP_MAGIC_PAGE ; 
 int KVM_MAGIC_PAGE ; 
 int MAGIC_PAGE_FLAG_NOT_MAPPED_NX ; 
 int /*<<< orphan*/  epapr_hypercall (int*,int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_map_magic_page(void *data)
{
	u32 *features = data;

	ulong in[8] = {0};
	ulong out[8];

	in[0] = KVM_MAGIC_PAGE;
	in[1] = KVM_MAGIC_PAGE | MAGIC_PAGE_FLAG_NOT_MAPPED_NX;

	epapr_hypercall(in, out, KVM_HCALL_TOKEN(KVM_HC_PPC_MAP_MAGIC_PAGE));

	*features = out[0];
}