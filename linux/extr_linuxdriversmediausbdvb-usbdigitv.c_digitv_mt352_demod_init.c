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
struct dvb_frontend {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mt352_write (struct dvb_frontend*,int*,int) ; 

__attribute__((used)) static int digitv_mt352_demod_init(struct dvb_frontend *fe)
{
	static u8 reset_buf[] = { 0x89, 0x38,  0x8a, 0x2d, 0x50, 0x80 };
	static u8 init_buf[] = { 0x68, 0xa0,  0x8e, 0x40,  0x53, 0x50,
			0x67, 0x20,  0x7d, 0x01,  0x7c, 0x00,  0x7a, 0x00,
			0x79, 0x20,  0x57, 0x05,  0x56, 0x31,  0x88, 0x0f,
			0x75, 0x32 };
	int i;

	for (i = 0; i < ARRAY_SIZE(reset_buf); i += 2)
		mt352_write(fe, &reset_buf[i], 2);

	msleep(1);

	for (i = 0; i < ARRAY_SIZE(init_buf); i += 2)
		mt352_write(fe, &init_buf[i], 2);

	return 0;
}