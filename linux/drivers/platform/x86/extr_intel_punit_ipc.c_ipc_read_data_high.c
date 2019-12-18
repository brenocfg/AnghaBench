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
struct TYPE_3__ {scalar_t__** base; } ;
typedef  size_t IPC_TYPE ;
typedef  TYPE_1__ IPC_DEV ;

/* Variables and functions */
 size_t BASE_DATA ; 
 scalar_t__ OFFSET_DATA_HIGH ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 

__attribute__((used)) static inline u32 ipc_read_data_high(IPC_DEV *ipcdev, IPC_TYPE type)
{
	return readl(ipcdev->base[type][BASE_DATA] + OFFSET_DATA_HIGH);
}