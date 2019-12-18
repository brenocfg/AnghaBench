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
struct applespi_key_translation {unsigned int to; } ;

/* Variables and functions */
 int /*<<< orphan*/  apple_iso_keyboard ; 
 struct applespi_key_translation* applespi_find_translation (int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static unsigned int applespi_translate_iso_layout(unsigned int key)
{
	const struct applespi_key_translation *trans;

	trans = applespi_find_translation(apple_iso_keyboard, key);
	if (trans)
		key = trans->to;

	return key;
}