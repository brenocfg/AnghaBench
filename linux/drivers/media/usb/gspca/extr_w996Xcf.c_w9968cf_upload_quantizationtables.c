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
typedef  int u16 ;
struct sd {int dummy; } ;

/* Variables and functions */
 unsigned int* UV_QUANTABLE ; 
 unsigned int* Y_QUANTABLE ; 
 int /*<<< orphan*/  reg_w (struct sd*,int,int) ; 

__attribute__((used)) static void w9968cf_upload_quantizationtables(struct sd *sd)
{
	u16 a, b;
	int i, j;

	reg_w(sd, 0x39, 0x0010); /* JPEG clock enable */

	for (i = 0, j = 0; i < 32; i++, j += 2) {
		a = Y_QUANTABLE[j] | ((unsigned)(Y_QUANTABLE[j + 1]) << 8);
		b = UV_QUANTABLE[j] | ((unsigned)(UV_QUANTABLE[j + 1]) << 8);
		reg_w(sd, 0x40 + i, a);
		reg_w(sd, 0x60 + i, b);
	}
	reg_w(sd, 0x39, 0x0012); /* JPEG encoder enable */
}