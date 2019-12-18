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
struct sti_struct {int dummy; } ;
typedef  void sti_glob_cfg ;

/* Variables and functions */
 unsigned long STI_PTR (void*) ; 
 scalar_t__ WARN_ONCE (int,char*) ; 
 int pdc_sti_call (unsigned long,unsigned long,unsigned long,unsigned long,unsigned long) ; 

int sti_call(const struct sti_struct *sti, unsigned long func,
		const void *flags, void *inptr, void *outptr,
		struct sti_glob_cfg *glob_cfg)
{
	unsigned long _flags = STI_PTR(flags);
	unsigned long _inptr = STI_PTR(inptr);
	unsigned long _outptr = STI_PTR(outptr);
	unsigned long _glob_cfg = STI_PTR(glob_cfg);
	int ret;

#ifdef CONFIG_64BIT
	/* Check for overflow when using 32bit STI on 64bit kernel. */
	if (WARN_ONCE(_flags>>32 || _inptr>>32 || _outptr>>32 || _glob_cfg>>32,
			"Out of 32bit-range pointers!"))
		return -1;
#endif

	ret = pdc_sti_call(func, _flags, _inptr, _outptr, _glob_cfg);

	return ret;
}