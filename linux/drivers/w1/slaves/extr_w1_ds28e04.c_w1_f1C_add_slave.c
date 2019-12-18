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
struct w1_slave {struct w1_f1C_data* family_data; } ;
struct w1_f1C_data {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct w1_f1C_data* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ w1_enable_crccheck ; 

__attribute__((used)) static int w1_f1C_add_slave(struct w1_slave *sl)
{
	struct w1_f1C_data *data = NULL;

	if (w1_enable_crccheck) {
		data = kzalloc(sizeof(struct w1_f1C_data), GFP_KERNEL);
		if (!data)
			return -ENOMEM;
		sl->family_data = data;
	}

	return 0;
}