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
struct TYPE_2__ {int /*<<< orphan*/  control2; int /*<<< orphan*/  control1; } ;

/* Variables and functions */
 TYPE_1__ reg ; 
 int /*<<< orphan*/  write_c0_perflo1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_perflo2 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int loongson3_starting_cpu(unsigned int cpu)
{
	write_c0_perflo1(reg.control1);
	write_c0_perflo2(reg.control2);
	return 0;
}