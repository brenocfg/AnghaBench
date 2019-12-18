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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct idt_ntb_dev {int /*<<< orphan*/  hwmon_mtx; } ;
typedef  enum idt_temp_val { ____Placeholder_idt_temp_val } idt_temp_val ;

/* Variables and functions */
 unsigned int IDT_SW_TMPADJ ; 
 unsigned int IDT_SW_TMPALARM ; 
#define  IDT_TEMP_HIGH 130 
#define  IDT_TEMP_LOW 129 
#define  IDT_TEMP_OFFSET 128 
 int IDT_TMPALARM_IRQ_MASK ; 
 int SET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TMPADJ_OFFSET ; 
 int /*<<< orphan*/  TMPALARM_HTEMP ; 
 int /*<<< orphan*/  TMPALARM_LTEMP ; 
 int /*<<< orphan*/  idt_sw_read (struct idt_ntb_dev*,unsigned int) ; 
 int /*<<< orphan*/  idt_sw_write (struct idt_ntb_dev*,unsigned int,int) ; 
 int /*<<< orphan*/  idt_temp_get_fmt (long const) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void idt_write_temp(struct idt_ntb_dev *ndev,
			   const enum idt_temp_val type, const long val)
{
	unsigned int reg;
	u32 data;
	u8 fmt;

	/* Retrieve the properly formatted temperature value */
	fmt = idt_temp_get_fmt(val);

	mutex_lock(&ndev->hwmon_mtx);
	switch (type) {
	case IDT_TEMP_LOW:
		reg = IDT_SW_TMPALARM;
		data = SET_FIELD(TMPALARM_LTEMP, idt_sw_read(ndev, reg), fmt) &
			~IDT_TMPALARM_IRQ_MASK;
		break;
	case IDT_TEMP_HIGH:
		reg = IDT_SW_TMPALARM;
		data = SET_FIELD(TMPALARM_HTEMP, idt_sw_read(ndev, reg), fmt) &
			~IDT_TMPALARM_IRQ_MASK;
		break;
	case IDT_TEMP_OFFSET:
		reg = IDT_SW_TMPADJ;
		data = SET_FIELD(TMPADJ_OFFSET, idt_sw_read(ndev, reg), fmt);
		break;
	default:
		goto inval_spin_unlock;
	}

	idt_sw_write(ndev, reg, data);

inval_spin_unlock:
	mutex_unlock(&ndev->hwmon_mtx);
}