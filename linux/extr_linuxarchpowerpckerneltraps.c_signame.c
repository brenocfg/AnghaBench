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
#define  SIGBUS 132 
#define  SIGFPE 131 
#define  SIGILL 130 
#define  SIGSEGV 129 
#define  SIGTRAP 128 

__attribute__((used)) static const char *signame(int signr)
{
	switch (signr) {
	case SIGBUS:	return "bus error";
	case SIGFPE:	return "floating point exception";
	case SIGILL:	return "illegal instruction";
	case SIGSEGV:	return "segfault";
	case SIGTRAP:	return "unhandled trap";
	}

	return "unknown signal";
}