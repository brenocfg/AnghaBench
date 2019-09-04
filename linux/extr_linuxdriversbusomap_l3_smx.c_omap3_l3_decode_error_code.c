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
typedef  int u64 ;
typedef  enum omap3_l3_code { ____Placeholder_omap3_l3_code } omap3_l3_code ;

/* Variables and functions */
 int L3_ERROR_LOG_CODE ; 

__attribute__((used)) static inline enum omap3_l3_code omap3_l3_decode_error_code(u64 error)
{
	return (error & 0x0f000000) >> L3_ERROR_LOG_CODE;
}