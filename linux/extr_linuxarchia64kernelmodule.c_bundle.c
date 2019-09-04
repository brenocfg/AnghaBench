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
typedef  int uint64_t ;
struct insn {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline uint64_t
bundle (const struct insn *insn)
{
	return (uint64_t) insn & ~0xfUL;
}