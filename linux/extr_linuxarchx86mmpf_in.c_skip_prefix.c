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
struct prefix_bits {int shorted; int enlarged; int rexr; int rex; } ;

/* Variables and functions */
 int ARRAY_SIZE (unsigned char*) ; 
 unsigned char* prefix_codes ; 

__attribute__((used)) static int skip_prefix(unsigned char *addr, struct prefix_bits *prf)
{
	int i;
	unsigned char *p = addr;
	prf->shorted = 0;
	prf->enlarged = 0;
	prf->rexr = 0;
	prf->rex = 0;

restart:
	for (i = 0; i < ARRAY_SIZE(prefix_codes); i++) {
		if (*p == prefix_codes[i]) {
			if (*p == 0x66)
				prf->shorted = 1;
#ifdef __amd64__
			if ((*p & 0xf8) == 0x48)
				prf->enlarged = 1;
			if ((*p & 0xf4) == 0x44)
				prf->rexr = 1;
			if ((*p & 0xf0) == 0x40)
				prf->rex = 1;
#endif
			p++;
			goto restart;
		}
	}

	return (p - addr);
}