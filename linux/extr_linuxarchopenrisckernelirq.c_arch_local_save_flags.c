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

/* Variables and functions */
 int /*<<< orphan*/  SPR_SR ; 
 unsigned long SPR_SR_IEE ; 
 unsigned long SPR_SR_TEE ; 
 unsigned long mfspr (int /*<<< orphan*/ ) ; 

unsigned long arch_local_save_flags(void)
{
	return mfspr(SPR_SR) & (SPR_SR_IEE|SPR_SR_TEE);
}