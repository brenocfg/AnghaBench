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
struct async_icount {int /*<<< orphan*/  dcd; int /*<<< orphan*/  rng; int /*<<< orphan*/  cts; int /*<<< orphan*/  dsr; } ;

/* Variables and functions */
 unsigned char MCT_U232_MSR_DCD ; 
 unsigned char MCT_U232_MSR_DCTS ; 
 unsigned char MCT_U232_MSR_DDSR ; 
 unsigned char MCT_U232_MSR_DRI ; 

__attribute__((used)) static void mct_u232_msr_to_icount(struct async_icount *icount,
						unsigned char msr)
{
	/* Translate Control Line states */
	if (msr & MCT_U232_MSR_DDSR)
		icount->dsr++;
	if (msr & MCT_U232_MSR_DCTS)
		icount->cts++;
	if (msr & MCT_U232_MSR_DRI)
		icount->rng++;
	if (msr & MCT_U232_MSR_DCD)
		icount->dcd++;
}