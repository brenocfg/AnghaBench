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
typedef  int /*<<< orphan*/  u64 ;
struct kernel_param {scalar_t__ arg; } ;

/* Variables and functions */
 int sprintf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int srpt_get_u64_x(char *buffer, const struct kernel_param *kp)
{
	return sprintf(buffer, "0x%016llx", *(u64 *)kp->arg);
}