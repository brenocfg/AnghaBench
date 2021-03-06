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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIT (int) ; 
 scalar_t__ dell_smbios_find_token (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kbd_token_bits ; 
 int /*<<< orphan*/ * kbd_tokens ; 

__attribute__((used)) static inline void kbd_init_tokens(void)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(kbd_tokens); ++i)
		if (dell_smbios_find_token(kbd_tokens[i]))
			kbd_token_bits |= BIT(i);
}