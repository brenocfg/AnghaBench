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
struct bfa_tskim_s {int /*<<< orphan*/  wc; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfa_wc_down (int /*<<< orphan*/ *) ; 

void
bfa_tskim_iodone(struct bfa_tskim_s *tskim)
{
	bfa_wc_down(&tskim->wc);
}