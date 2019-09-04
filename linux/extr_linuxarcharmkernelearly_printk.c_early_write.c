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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (char*,char const*,unsigned int) ; 
 unsigned int min (unsigned int,int) ; 
 int /*<<< orphan*/  printascii (char*) ; 

__attribute__((used)) static void early_write(const char *s, unsigned n)
{
	char buf[128];
	while (n) {
		unsigned l = min(n, sizeof(buf)-1);
		memcpy(buf, s, l);
		buf[l] = 0;
		s += l;
		n -= l;
		printascii(buf);
	}
}