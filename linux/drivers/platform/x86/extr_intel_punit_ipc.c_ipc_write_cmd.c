#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_3__ {int /*<<< orphan*/ ** base; } ;
typedef  size_t IPC_TYPE ;
typedef  TYPE_1__ IPC_DEV ;

/* Variables and functions */
 size_t BASE_IFACE ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ipc_write_cmd(IPC_DEV *ipcdev, IPC_TYPE type, u32 cmd)
{
	writel(cmd, ipcdev->base[type][BASE_IFACE]);
}