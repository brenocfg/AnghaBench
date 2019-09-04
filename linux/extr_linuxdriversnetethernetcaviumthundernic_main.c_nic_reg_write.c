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
typedef  scalar_t__ u64 ;
struct nicpf {scalar_t__ reg_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  writeq_relaxed (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void nic_reg_write(struct nicpf *nic, u64 offset, u64 val)
{
	writeq_relaxed(val, nic->reg_base + offset);
}