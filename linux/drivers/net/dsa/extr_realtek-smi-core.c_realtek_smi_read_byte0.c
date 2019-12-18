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
typedef  int u32 ;
struct realtek_smi {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  realtek_smi_read_bits (struct realtek_smi*,int,int*) ; 
 int /*<<< orphan*/  realtek_smi_write_bits (struct realtek_smi*,int,int) ; 

__attribute__((used)) static int realtek_smi_read_byte0(struct realtek_smi *smi, u8 *data)
{
	u32 t;

	/* Read data */
	realtek_smi_read_bits(smi, 8, &t);
	*data = (t & 0xff);

	/* Send an ACK */
	realtek_smi_write_bits(smi, 0x00, 1);

	return 0;
}