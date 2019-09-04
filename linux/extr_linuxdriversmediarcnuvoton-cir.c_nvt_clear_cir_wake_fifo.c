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
typedef  int u8 ;
struct nvt_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_WAKE_FIFOCON ; 
 int CIR_WAKE_FIFOCON_RXFIFOCLR ; 
 int /*<<< orphan*/  CIR_WAKE_IRCON ; 
 int CIR_WAKE_IRCON_MODE0 ; 
 int nvt_cir_wake_reg_read (struct nvt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_cir_wake_reg_write (struct nvt_dev*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvt_clear_cir_wake_fifo(struct nvt_dev *nvt)
{
	u8 val, config;

	config = nvt_cir_wake_reg_read(nvt, CIR_WAKE_IRCON);

	/* clearing wake fifo works in learning mode only */
	nvt_cir_wake_reg_write(nvt, config & ~CIR_WAKE_IRCON_MODE0,
			       CIR_WAKE_IRCON);

	val = nvt_cir_wake_reg_read(nvt, CIR_WAKE_FIFOCON);
	nvt_cir_wake_reg_write(nvt, val | CIR_WAKE_FIFOCON_RXFIFOCLR,
			       CIR_WAKE_FIFOCON);

	nvt_cir_wake_reg_write(nvt, config, CIR_WAKE_IRCON);
}