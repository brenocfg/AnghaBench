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
struct pt3_i2cbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_DATA_H_ACK0 ; 
 int /*<<< orphan*/  I_DATA_H_NOP ; 
 int /*<<< orphan*/  I_DATA_L_NOP ; 
 int /*<<< orphan*/  cmdbuf_add (struct pt3_i2cbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_byte_write(struct pt3_i2cbuf *cbuf, u8 val)
{
	u8 mask;

	for (mask = 0x80; mask > 0; mask >>= 1)
		cmdbuf_add(cbuf, (val & mask) ? I_DATA_H_NOP : I_DATA_L_NOP);
	cmdbuf_add(cbuf, I_DATA_H_ACK0);
}