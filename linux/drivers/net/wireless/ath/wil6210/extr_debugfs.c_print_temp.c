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
struct seq_file {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
#define  WMI_INVALID_TEMPERATURE 128 
 int /*<<< orphan*/  abs (int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,...) ; 

__attribute__((used)) static void print_temp(struct seq_file *s, const char *prefix, s32 t)
{
	switch (t) {
	case 0:
	case WMI_INVALID_TEMPERATURE:
		seq_printf(s, "%s N/A\n", prefix);
	break;
	default:
		seq_printf(s, "%s %s%d.%03d\n", prefix, (t < 0 ? "-" : ""),
			   abs(t / 1000), abs(t % 1000));
		break;
	}
}