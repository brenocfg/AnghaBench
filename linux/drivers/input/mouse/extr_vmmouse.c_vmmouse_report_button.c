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
struct psmouse {int dummy; } ;
struct input_dev {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  input_report_key (struct input_dev*,unsigned int,int) ; 
 scalar_t__ test_bit (unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmmouse_report_button(struct psmouse *psmouse,
				  struct input_dev *abs_dev,
				  struct input_dev *rel_dev,
				  struct input_dev *pref_dev,
				  unsigned int code, int value)
{
	if (test_bit(code, abs_dev->key))
		pref_dev = abs_dev;
	else if (test_bit(code, rel_dev->key))
		pref_dev = rel_dev;

	input_report_key(pref_dev, code, value);
}