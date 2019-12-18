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
 int kvmgt_rw_gpa (unsigned long,unsigned long,void*,unsigned long,int) ; 

__attribute__((used)) static int kvmgt_write_gpa(unsigned long handle, unsigned long gpa,
			void *buf, unsigned long len)
{
	return kvmgt_rw_gpa(handle, gpa, buf, len, true);
}