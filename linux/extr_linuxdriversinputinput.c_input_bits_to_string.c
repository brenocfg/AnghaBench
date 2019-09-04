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

/* Variables and functions */
 int snprintf (char*,int,char*,unsigned long) ; 

__attribute__((used)) static int input_bits_to_string(char *buf, int buf_size,
				unsigned long bits, bool skip_empty)
{
	return bits || !skip_empty ?
		snprintf(buf, buf_size, "%lx", bits) : 0;
}