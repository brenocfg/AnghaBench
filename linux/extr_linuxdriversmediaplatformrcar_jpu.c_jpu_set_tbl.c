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
typedef  scalar_t__ u32 ;
struct jpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  jpu_write (struct jpu*,unsigned int const,scalar_t__) ; 

__attribute__((used)) static void jpu_set_tbl(struct jpu *jpu, u32 reg, const unsigned int *tbl,
			unsigned int len) {
	unsigned int i;

	for (i = 0; i < len; i++)
		jpu_write(jpu, tbl[i], reg + (i << 2));
}