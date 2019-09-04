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
typedef  int uint32_t ;
typedef  enum a3xx_threadsize { ____Placeholder_a3xx_threadsize } a3xx_threadsize ;

/* Variables and functions */
 int A5XX_SP_FS_CTRL_REG0_THREADSIZE__MASK ; 
 int A5XX_SP_FS_CTRL_REG0_THREADSIZE__SHIFT ; 

__attribute__((used)) static inline uint32_t A5XX_SP_FS_CTRL_REG0_THREADSIZE(enum a3xx_threadsize val)
{
	return ((val) << A5XX_SP_FS_CTRL_REG0_THREADSIZE__SHIFT) & A5XX_SP_FS_CTRL_REG0_THREADSIZE__MASK;
}