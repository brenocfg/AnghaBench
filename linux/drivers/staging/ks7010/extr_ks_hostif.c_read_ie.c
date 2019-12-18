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
typedef  unsigned char u8 ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,unsigned char) ; 

__attribute__((used)) static u8 read_ie(unsigned char *bp, u8 max, u8 *body)
{
	u8 size = (*(bp + 1) <= max) ? *(bp + 1) : max;

	memcpy(body, bp + 2, size);
	return size;
}