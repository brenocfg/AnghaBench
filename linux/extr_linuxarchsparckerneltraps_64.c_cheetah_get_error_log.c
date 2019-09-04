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
struct cheetah_err_info {int dummy; } ;

/* Variables and functions */
 unsigned long CHAFSR_TL1 ; 
 struct cheetah_err_info* cheetah_error_log ; 
 int smp_processor_id () ; 

__attribute__((used)) static inline struct cheetah_err_info *cheetah_get_error_log(unsigned long afsr)
{
	struct cheetah_err_info *p;
	int cpu = smp_processor_id();

	if (!cheetah_error_log)
		return NULL;

	p = cheetah_error_log + (cpu * 2);
	if ((afsr & CHAFSR_TL1) != 0UL)
		p++;

	return p;
}