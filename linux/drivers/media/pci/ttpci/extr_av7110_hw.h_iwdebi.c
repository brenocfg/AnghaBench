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
typedef  int /*<<< orphan*/  u32 ;
struct av7110 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  av7110_debiwrite (struct av7110*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static inline void iwdebi(struct av7110 *av7110, u32 config, int addr, u32 val, unsigned int count)
{
	av7110_debiwrite(av7110, config, addr, val, count);
}