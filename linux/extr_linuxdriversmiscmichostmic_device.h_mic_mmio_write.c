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
typedef  scalar_t__ u32 ;
struct mic_mw {scalar_t__ va; } ;

/* Variables and functions */
 int /*<<< orphan*/  iowrite32 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void
mic_mmio_write(struct mic_mw *mw, u32 val, u32 offset)
{
	iowrite32(val, mw->va + offset);
}