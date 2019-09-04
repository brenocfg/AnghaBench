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
typedef  size_t u64 ;

/* Variables and functions */
 size_t CSR_FCP_COMMAND ; 
 size_t CSR_FCP_END ; 
 size_t CSR_REGISTER_BASE ; 

__attribute__((used)) static bool is_in_fcp_region(u64 offset, size_t length)
{
	return offset >= (CSR_REGISTER_BASE | CSR_FCP_COMMAND) &&
		offset + length <= (CSR_REGISTER_BASE | CSR_FCP_END);
}