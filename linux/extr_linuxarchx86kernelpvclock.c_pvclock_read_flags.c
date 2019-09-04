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
typedef  int u8 ;
struct pvclock_vcpu_time_info {int flags; } ;

/* Variables and functions */
 unsigned int pvclock_read_begin (struct pvclock_vcpu_time_info*) ; 
 scalar_t__ pvclock_read_retry (struct pvclock_vcpu_time_info*,unsigned int) ; 
 int valid_flags ; 

u8 pvclock_read_flags(struct pvclock_vcpu_time_info *src)
{
	unsigned version;
	u8 flags;

	do {
		version = pvclock_read_begin(src);
		flags = src->flags;
	} while (pvclock_read_retry(src, version));

	return flags & valid_flags;
}