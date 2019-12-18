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
typedef  scalar_t__ irq_hw_number_t ;

/* Variables and functions */
 int ITYPE_mskVECTOR ; 
 int ITYPE_offVECTOR ; 
 int /*<<< orphan*/  NDS32_SR_ITYPE ; 
 scalar_t__ NDS32_VECTOR_offINTERRUPT ; 
 int __nds32__mfsr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irq_hw_number_t get_intr_src(void)
{
	return ((__nds32__mfsr(NDS32_SR_ITYPE) & ITYPE_mskVECTOR) >> ITYPE_offVECTOR)
		- NDS32_VECTOR_offINTERRUPT;
}