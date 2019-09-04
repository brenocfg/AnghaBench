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

/* Variables and functions */
 unsigned long per_cpu (int /*<<< orphan*/ ,int) ; 
 int uv_apicid_to_pnode (unsigned long) ; 
 int /*<<< orphan*/  uv_hub_send_ipi (int,unsigned long,int) ; 
 int /*<<< orphan*/  x86_cpu_to_apicid ; 

__attribute__((used)) static void uv_send_IPI_one(int cpu, int vector)
{
	unsigned long apicid;
	int pnode;

	apicid = per_cpu(x86_cpu_to_apicid, cpu);
	pnode = uv_apicid_to_pnode(apicid);
	uv_hub_send_ipi(pnode, apicid, vector);
}