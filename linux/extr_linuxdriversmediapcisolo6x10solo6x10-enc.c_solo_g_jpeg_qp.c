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
struct solo_dev {scalar_t__ type; unsigned int* jpeg_qp; } ;

/* Variables and functions */
 scalar_t__ SOLO_DEV_6010 ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

int solo_g_jpeg_qp(struct solo_dev *solo_dev, unsigned int ch)
{
	int idx;

	if (solo_dev->type == SOLO_DEV_6010)
		return 2;

	if (WARN_ON_ONCE(ch > 31))
		return 2;

	if (ch < 16) {
		idx = 0;
	} else {
		ch -= 16;
		idx = 1;
	}
	ch *= 2;

	return (solo_dev->jpeg_qp[idx] >> ch) & 3;
}