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
struct qxl_head {scalar_t__ height; scalar_t__ width; } ;

/* Variables and functions */

__attribute__((used)) static bool qxl_head_enabled(struct qxl_head *head)
{
	return head->width && head->height;
}