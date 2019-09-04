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
typedef  int /*<<< orphan*/  be128 ;

/* Variables and functions */
 int /*<<< orphan*/  be128_xor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gf128mul_x8_bbe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gf128mul_x_bbe (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

void gf128mul_bbe(be128 *r, const be128 *b)
{
	be128 p[8];
	int i;

	p[0] = *r;
	for (i = 0; i < 7; ++i)
		gf128mul_x_bbe(&p[i + 1], &p[i]);

	memset(r, 0, sizeof(*r));
	for (i = 0;;) {
		u8 ch = ((u8 *)b)[i];

		if (ch & 0x80)
			be128_xor(r, r, &p[7]);
		if (ch & 0x40)
			be128_xor(r, r, &p[6]);
		if (ch & 0x20)
			be128_xor(r, r, &p[5]);
		if (ch & 0x10)
			be128_xor(r, r, &p[4]);
		if (ch & 0x08)
			be128_xor(r, r, &p[3]);
		if (ch & 0x04)
			be128_xor(r, r, &p[2]);
		if (ch & 0x02)
			be128_xor(r, r, &p[1]);
		if (ch & 0x01)
			be128_xor(r, r, &p[0]);

		if (++i >= 16)
			break;

		gf128mul_x8_bbe(r);
	}
}