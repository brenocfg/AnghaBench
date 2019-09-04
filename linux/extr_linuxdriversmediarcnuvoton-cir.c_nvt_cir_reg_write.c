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
typedef  scalar_t__ u8 ;
struct nvt_dev {scalar_t__ cir_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  outb (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void nvt_cir_reg_write(struct nvt_dev *nvt, u8 val, u8 offset)
{
	outb(val, nvt->cir_addr + offset);
}