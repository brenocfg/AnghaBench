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
struct ipu_di {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DI_DW_GEN (int) ; 
 int DI_DW_GEN_ACCESS_SIZE_OFFSET ; 
 int DI_DW_GEN_COMPONENT_SIZE_OFFSET ; 
 int /*<<< orphan*/  ipu_di_write (struct ipu_di*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ipu_di_data_wave_config(struct ipu_di *di,
				     int wave_gen,
				     int access_size, int component_size)
{
	u32 reg;
	reg = (access_size << DI_DW_GEN_ACCESS_SIZE_OFFSET) |
	    (component_size << DI_DW_GEN_COMPONENT_SIZE_OFFSET);
	ipu_di_write(di, reg, DI_DW_GEN(wave_gen));
}