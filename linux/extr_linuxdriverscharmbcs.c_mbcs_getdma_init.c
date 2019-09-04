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
struct getdma {int DoneIntEnable; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct getdma*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void mbcs_getdma_init(struct getdma *gdma)
{
	memset(gdma, 0, sizeof(struct getdma));
	gdma->DoneIntEnable = 1;
}