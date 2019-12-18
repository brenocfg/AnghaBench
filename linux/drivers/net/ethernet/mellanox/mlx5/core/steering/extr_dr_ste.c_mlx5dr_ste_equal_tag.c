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
struct dr_hw_ste_format {int /*<<< orphan*/  tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  DR_STE_SIZE_TAG ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

bool mlx5dr_ste_equal_tag(void *src, void *dst)
{
	struct dr_hw_ste_format *s_hw_ste = (struct dr_hw_ste_format *)src;
	struct dr_hw_ste_format *d_hw_ste = (struct dr_hw_ste_format *)dst;

	return !memcmp(s_hw_ste->tag, d_hw_ste->tag, DR_STE_SIZE_TAG);
}