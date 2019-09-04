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
 int /*<<< orphan*/  CHAN_MASK (int) ; 
 scalar_t__ IPCMxDCLEAR (int) ; 
 scalar_t__ IPCMxMCLEAR (int) ; 
 scalar_t__ ipc_base ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void clear_destination(int source, int mbox)
{
	writel_relaxed(CHAN_MASK(source), ipc_base + IPCMxDCLEAR(mbox));
	writel_relaxed(CHAN_MASK(source), ipc_base + IPCMxMCLEAR(mbox));
}