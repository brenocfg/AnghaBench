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
typedef  int u32 ;

/* Variables and functions */
 int host1x_uclass_indoff_autoinc_f (int) ; 
 int host1x_uclass_indoff_indbe_f (int) ; 
 int host1x_uclass_indoff_indmodid_f (unsigned int) ; 
 int host1x_uclass_indoff_indroffset_f (unsigned int) ; 

__attribute__((used)) static inline u32 host1x_class_host_indoff_reg_write(
	unsigned mod_id, unsigned offset, bool auto_inc)
{
	u32 v = host1x_uclass_indoff_indbe_f(0xf)
		| host1x_uclass_indoff_indmodid_f(mod_id)
		| host1x_uclass_indoff_indroffset_f(offset);
	if (auto_inc)
		v |= host1x_uclass_indoff_autoinc_f(1);
	return v;
}