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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*,int,int) ; 

__attribute__((used)) static inline int mtk_jpeg_verify_align(u32 val, int align, u32 reg)
{
	if (val & (align - 1)) {
		pr_err("mtk-jpeg: write reg %x without %d align\n", reg, align);
		return -1;
	}

	return 0;
}