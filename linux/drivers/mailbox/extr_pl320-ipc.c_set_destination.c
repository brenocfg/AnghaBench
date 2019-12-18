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
 scalar_t__ IPCMxDSET (int) ; 
 scalar_t__ IPCMxMSET (int) ; 
 scalar_t__ ipc_base ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void set_destination(int source, int mbox)
{
	writel_relaxed(CHAN_MASK(source), ipc_base + IPCMxDSET(mbox));
	writel_relaxed(CHAN_MASK(source), ipc_base + IPCMxMSET(mbox));
}