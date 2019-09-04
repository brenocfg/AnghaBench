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
struct nvkm_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  magic_ (struct nvkm_device*,int,int) ; 

__attribute__((used)) static void
magic(struct nvkm_device *device, u32 ctrl)
{
	magic_(device, 0x8000a41f | ctrl, 6);
	magic_(device, 0x80000421 | ctrl, 1);
}