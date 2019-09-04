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
typedef  int uint32_t ;

/* Variables and functions */
 int ALIGN (int,int) ; 

__attribute__((used)) static inline uint32_t armada_pitch(uint32_t width, uint32_t bpp)
{
	uint32_t pitch = bpp != 4 ? width * ((bpp + 7) / 8) : width / 2;

	/* 88AP510 spec recommends pitch be a multiple of 128 */
	return ALIGN(pitch, 128);
}