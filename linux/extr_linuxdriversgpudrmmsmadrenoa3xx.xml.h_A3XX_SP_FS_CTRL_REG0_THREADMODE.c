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
typedef  enum a3xx_threadmode { ____Placeholder_a3xx_threadmode } a3xx_threadmode ;

/* Variables and functions */
 int A3XX_SP_FS_CTRL_REG0_THREADMODE__MASK ; 
 int A3XX_SP_FS_CTRL_REG0_THREADMODE__SHIFT ; 

__attribute__((used)) static inline uint32_t A3XX_SP_FS_CTRL_REG0_THREADMODE(enum a3xx_threadmode val)
{
	return ((val) << A3XX_SP_FS_CTRL_REG0_THREADMODE__SHIFT) & A3XX_SP_FS_CTRL_REG0_THREADMODE__MASK;
}