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
typedef  int /*<<< orphan*/  u_char ;

/* Variables and functions */

__attribute__((used)) static inline void
isdn_audio_tlookup(const u_char *table, u_char *buff, unsigned long n)
{
#ifdef __i386__
	unsigned long d0, d1, d2, d3;
	__asm__ __volatile__(
		"cld\n"
		"1:\tlodsb\n\t"
		"xlatb\n\t"
		"stosb\n\t"
		"loop 1b\n\t"
		:	"=&b"(d0), "=&c"(d1), "=&D"(d2), "=&S"(d3)
		:	"0"((long) table), "1"(n), "2"((long) buff), "3"((long) buff)
		:	"memory", "ax");
#else
	while (n--)
		*buff = table[*(unsigned char *)buff], buff++;
#endif
}