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
struct hidma_lldev {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  hidma_ll_inthandler (int,struct hidma_lldev*) ; 

__attribute__((used)) static irqreturn_t hidma_chirq_handler(int chirq, void *arg)
{
	struct hidma_lldev *lldev = arg;

	/*
	 * All interrupts are request driven.
	 * HW doesn't send an interrupt by itself.
	 */
	return hidma_ll_inthandler(chirq, lldev);
}