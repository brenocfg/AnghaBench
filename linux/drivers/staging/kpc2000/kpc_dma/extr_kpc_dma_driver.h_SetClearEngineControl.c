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
typedef  int /*<<< orphan*/  u32 ;
struct kpc_dma_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GetEngineControl (struct kpc_dma_device*) ; 
 int /*<<< orphan*/  WriteEngineControl (struct kpc_dma_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
void  SetClearEngineControl(struct kpc_dma_device *eng, u32 set_bits, u32 clear_bits)
{
	u32 val = GetEngineControl(eng);

	val |= set_bits;
	val &= ~clear_bits;
	WriteEngineControl(eng, val);
}