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
 int inb_p (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*,int,int,int,int) ; 
 scalar_t__ synth_port ; 

__attribute__((used)) static char *oops(void)
{
	int s1, s2, s3, s4;

	s1 = inb_p(synth_port);
	s2 = inb_p(synth_port + 1);
	s3 = inb_p(synth_port + 2);
	s4 = inb_p(synth_port + 3);
	pr_warn("synth timeout %d %d %d %d\n", s1, s2, s3, s4);
	return NULL;
}