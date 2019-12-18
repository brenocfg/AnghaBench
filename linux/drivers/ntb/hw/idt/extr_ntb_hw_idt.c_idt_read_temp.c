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
struct idt_ntb_dev {int dummy; } ;
typedef  enum idt_temp_val { ____Placeholder_idt_temp_val } idt_temp_val ;

/* Variables and functions */
 int /*<<< orphan*/  GET_FIELD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDT_SW_TMPADJ ; 
 int /*<<< orphan*/  IDT_SW_TMPSTS ; 
#define  IDT_TEMP_CUR 131 
#define  IDT_TEMP_HIGH 130 
#define  IDT_TEMP_LOW 129 
#define  IDT_TEMP_OFFSET 128 
 int /*<<< orphan*/  TMPADJ_OFFSET ; 
 int /*<<< orphan*/  TMPSTS_HTEMP ; 
 int /*<<< orphan*/  TMPSTS_LTEMP ; 
 int /*<<< orphan*/  TMPSTS_TEMP ; 
 long idt_get_temp_sval (int /*<<< orphan*/ ) ; 
 long idt_get_temp_uval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idt_sw_read (struct idt_ntb_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idt_read_temp(struct idt_ntb_dev *ndev,
			  const enum idt_temp_val type, long *val)
{
	u32 data;

	/* Alter the temperature field in accordance with the passed type */
	switch (type) {
	case IDT_TEMP_CUR:
		data = GET_FIELD(TMPSTS_TEMP,
				 idt_sw_read(ndev, IDT_SW_TMPSTS));
		break;
	case IDT_TEMP_LOW:
		data = GET_FIELD(TMPSTS_LTEMP,
				 idt_sw_read(ndev, IDT_SW_TMPSTS));
		break;
	case IDT_TEMP_HIGH:
		data = GET_FIELD(TMPSTS_HTEMP,
				 idt_sw_read(ndev, IDT_SW_TMPSTS));
		break;
	case IDT_TEMP_OFFSET:
		/* This is the only field with signed 0:7:1 format */
		data = GET_FIELD(TMPADJ_OFFSET,
				 idt_sw_read(ndev, IDT_SW_TMPADJ));
		*val = idt_get_temp_sval(data);
		return;
	default:
		data = GET_FIELD(TMPSTS_TEMP,
				 idt_sw_read(ndev, IDT_SW_TMPSTS));
		break;
	}

	/* The rest of the fields accept unsigned 0:7:1 format */
	*val = idt_get_temp_uval(data);
}