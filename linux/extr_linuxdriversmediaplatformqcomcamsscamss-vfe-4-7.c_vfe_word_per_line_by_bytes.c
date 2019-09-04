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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int CALC_WORD (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int vfe_word_per_line_by_bytes(u32 bytes_per_line)
{
	return CALC_WORD(bytes_per_line, 1, 8);
}