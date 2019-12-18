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
struct venus_inst {int dummy; } ;

/* Variables and functions */
 int intbufs_unset_buffers (struct venus_inst*) ; 

int venus_helper_intbufs_free(struct venus_inst *inst)
{
	return intbufs_unset_buffers(inst);
}