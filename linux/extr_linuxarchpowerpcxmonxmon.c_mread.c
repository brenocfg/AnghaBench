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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;

/* Variables and functions */
 int /*<<< orphan*/  __delay (int) ; 
 int /*<<< orphan*/  bus_error_jmp ; 
 int catch_memory_errors ; 
 scalar_t__ setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 

__attribute__((used)) static int
mread(unsigned long adrs, void *buf, int size)
{
	volatile int n;
	char *p, *q;

	n = 0;
	if (setjmp(bus_error_jmp) == 0) {
		catch_memory_errors = 1;
		sync();
		p = (char *)adrs;
		q = (char *)buf;
		switch (size) {
		case 2:
			*(u16 *)q = *(u16 *)p;
			break;
		case 4:
			*(u32 *)q = *(u32 *)p;
			break;
		case 8:
			*(u64 *)q = *(u64 *)p;
			break;
		default:
			for( ; n < size; ++n) {
				*q++ = *p++;
				sync();
			}
		}
		sync();
		/* wait a little while to see if we get a machine check */
		__delay(200);
		n = size;
	}
	catch_memory_errors = 0;
	return n;
}