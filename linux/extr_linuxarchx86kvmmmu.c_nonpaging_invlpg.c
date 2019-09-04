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
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  hpa_t ;
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */

__attribute__((used)) static void nonpaging_invlpg(struct kvm_vcpu *vcpu, gva_t gva, hpa_t root)
{
}