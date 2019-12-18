#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct seq_file {int dummy; } ;
struct TYPE_3__ {int device; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* device_mapping ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,int /*<<< orphan*/ ) ; 

void via_odev_to_seq(struct seq_file *m, u32 odev)
{
	int i, count = 0;

	for (i = 0; i < ARRAY_SIZE(device_mapping); i++) {
		if (odev & device_mapping[i].device) {
			if (count > 0)
				seq_putc(m, ',');

			seq_puts(m, device_mapping[i].name);
			count++;
		}
	}

	seq_putc(m, '\n');
}