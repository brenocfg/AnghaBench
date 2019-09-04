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
typedef  int s16 ;

/* Variables and functions */

__attribute__((used)) static void add_deltas(s16 *deltas, const u8 *ref, int stride)
{
	int k, l;

	for (k = 0; k < 8; k++) {
		for (l = 0; l < 8; l++) {
			*deltas += *ref++;
			/*
			 * Due to quantizing, it might possible that the
			 * decoded coefficients are slightly out of range
			 */
			if (*deltas < 0)
				*deltas = 0;
			else if (*deltas > 255)
				*deltas = 255;
			deltas++;
		}
		ref += stride - 8;
	}
}