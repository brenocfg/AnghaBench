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
struct vsie_page {int /*<<< orphan*/ * scb_o; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;
typedef  scalar_t__ hpa_t ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  unpin_guest_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void unpin_scb(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page,
		      gpa_t gpa)
{
	hpa_t hpa = (hpa_t) vsie_page->scb_o;

	if (hpa)
		unpin_guest_page(vcpu->kvm, gpa, hpa);
	vsie_page->scb_o = NULL;
}