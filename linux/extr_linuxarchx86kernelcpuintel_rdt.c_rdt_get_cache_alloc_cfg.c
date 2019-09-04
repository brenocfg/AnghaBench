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
struct TYPE_4__ {scalar_t__ cos_max; } ;
union cpuid_0x10_x_edx {TYPE_1__ split; int /*<<< orphan*/  full; } ;
struct TYPE_5__ {int cbm_len; } ;
union cpuid_0x10_1_eax {TYPE_2__ split; int /*<<< orphan*/  full; } ;
typedef  int u32 ;
struct TYPE_6__ {int cbm_len; int shareable_bits; } ;
struct rdt_resource {int default_ctrl; int data_width; int alloc_capable; int alloc_enabled; TYPE_3__ cache; scalar_t__ num_closid; } ;

/* Variables and functions */
 int BIT_MASK (int) ; 
 int /*<<< orphan*/  cpuid_count (int,int,int /*<<< orphan*/ *,int*,int*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rdt_get_cache_alloc_cfg(int idx, struct rdt_resource *r)
{
	union cpuid_0x10_1_eax eax;
	union cpuid_0x10_x_edx edx;
	u32 ebx, ecx;

	cpuid_count(0x00000010, idx, &eax.full, &ebx, &ecx, &edx.full);
	r->num_closid = edx.split.cos_max + 1;
	r->cache.cbm_len = eax.split.cbm_len + 1;
	r->default_ctrl = BIT_MASK(eax.split.cbm_len + 1) - 1;
	r->cache.shareable_bits = ebx & r->default_ctrl;
	r->data_width = (r->cache.cbm_len + 3) / 4;
	r->alloc_capable = true;
	r->alloc_enabled = true;
}