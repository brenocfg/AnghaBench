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
struct pinctrl_pin_desc {int number; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int PINS ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int* pad_count ; 

__attribute__((used)) static void lantiq_load_pin_desc(struct pinctrl_pin_desc *d, int bank, int len)
{
	int base = bank * PINS;
	int i;

	for (i = 0; i < len; i++) {
		d[i].number = base + i;
		d[i].name = kasprintf(GFP_KERNEL, "io%d", base + i);
	}
	pad_count[bank] = len;
}