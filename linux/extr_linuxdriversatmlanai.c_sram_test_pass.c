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
struct lanai_dev {int dummy; } ;

/* Variables and functions */
 int SRAM_BYTES ; 
 int sram_test_word (struct lanai_dev const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sram_test_pass(const struct lanai_dev *lanai, u32 pattern)
{
	int offset, result = 0;
	for (offset = 0; offset < SRAM_BYTES && result == 0; offset += 4)
		result = sram_test_word(lanai, offset, pattern);
	return result;
}