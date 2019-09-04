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
 int INTR_INFO_INTR_TYPE_MASK ; 
 int INTR_INFO_VALID_MASK ; 
 int INTR_TYPE_NMI_INTR ; 

__attribute__((used)) static inline bool is_nmi(u32 intr_info)
{
	return (intr_info & (INTR_INFO_INTR_TYPE_MASK | INTR_INFO_VALID_MASK))
		== (INTR_TYPE_NMI_INTR | INTR_INFO_VALID_MASK);
}