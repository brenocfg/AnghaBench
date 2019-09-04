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

/* Variables and functions */
 int DIV_ROUND_UP (unsigned int const,int) ; 

__attribute__((used)) static inline u32 cio2_bytesperline(const unsigned int width)
{
	/*
	 * 64 bytes for every 50 pixels, the line length
	 * in bytes is multiple of 64 (line end alignment).
	 */
	return DIV_ROUND_UP(width, 50) * 64;
}