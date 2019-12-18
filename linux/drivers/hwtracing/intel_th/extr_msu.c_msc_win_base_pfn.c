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
struct msc_window {int dummy; } ;

/* Variables and functions */
 unsigned long PFN_DOWN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msc_win_base_dma (struct msc_window*) ; 

__attribute__((used)) static inline unsigned long
msc_win_base_pfn(struct msc_window *win)
{
	return PFN_DOWN(msc_win_base_dma(win));
}