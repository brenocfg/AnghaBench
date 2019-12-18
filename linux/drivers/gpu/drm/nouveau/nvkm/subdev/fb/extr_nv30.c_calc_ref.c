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
struct nvkm_fb {int dummy; } ;

/* Variables and functions */
 int calc_bias (struct nvkm_fb*,int,int,int) ; 
 int clamp (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
calc_ref(struct nvkm_fb *fb, int l, int k, int i)
{
	int j, x = 0;

	for (j = 0; j < 4; j++) {
		int m = (l >> (8 * i) & 0xff) + calc_bias(fb, k, i, j);

		x |= (0x80 | clamp(m, 0, 0x1f)) << (8 * j);
	}

	return x;
}