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
struct kvmppc_vcpu_e500 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvmppc_e500_id_table_reset_all (struct kvmppc_vcpu_e500*) ; 

void kvmppc_e500_tlbil_all(struct kvmppc_vcpu_e500 *vcpu_e500)
{
	kvmppc_e500_id_table_reset_all(vcpu_e500);
}