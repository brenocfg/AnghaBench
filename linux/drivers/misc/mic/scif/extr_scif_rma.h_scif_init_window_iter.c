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
struct scif_window_iter {scalar_t__ index; int /*<<< orphan*/  offset; } ;
struct scif_window {int /*<<< orphan*/  offset; } ;

/* Variables and functions */

__attribute__((used)) static inline void
scif_init_window_iter(struct scif_window *window, struct scif_window_iter *iter)
{
	iter->offset = window->offset;
	iter->index = 0;
}