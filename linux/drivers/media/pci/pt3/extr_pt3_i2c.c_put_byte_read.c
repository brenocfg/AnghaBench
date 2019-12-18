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
struct pt3_i2cbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_DATA_H_NOP ; 
 int /*<<< orphan*/  I_DATA_H_READ ; 
 int /*<<< orphan*/  I_DATA_L_NOP ; 
 int /*<<< orphan*/  cmdbuf_add (struct pt3_i2cbuf*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void put_byte_read(struct pt3_i2cbuf *cbuf, u32 size)
{
	int i, j;

	for (i = 0; i < size; i++) {
		for (j = 0; j < 8; j++)
			cmdbuf_add(cbuf, I_DATA_H_READ);
		cmdbuf_add(cbuf, (i == size - 1) ? I_DATA_H_NOP : I_DATA_L_NOP);
	}
}