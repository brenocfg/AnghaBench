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
 scalar_t__ IPCMxDR (int,int) ; 
 scalar_t__ IPCMxSEND (int) ; 
 scalar_t__ ipc_base ; 
 int /*<<< orphan*/  writel_relaxed (int,scalar_t__) ; 

__attribute__((used)) static void __ipc_send(int mbox, u32 *data)
{
	int i;
	for (i = 0; i < 7; i++)
		writel_relaxed(data[i], ipc_base + IPCMxDR(mbox, i));
	writel_relaxed(0x1, ipc_base + IPCMxSEND(mbox));
}