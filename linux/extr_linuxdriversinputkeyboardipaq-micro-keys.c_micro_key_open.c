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
struct ipaq_micro_keys {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 struct ipaq_micro_keys* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  micro_key_start (struct ipaq_micro_keys*) ; 

__attribute__((used)) static int micro_key_open(struct input_dev *input)
{
	struct ipaq_micro_keys *keys = input_get_drvdata(input);

	micro_key_start(keys);

	return 0;
}