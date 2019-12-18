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
struct tcw {int r; int w; int /*<<< orphan*/  flags; int /*<<< orphan*/  format; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCW_FLAGS_TIDAW_FORMAT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TCW_FORMAT_DEFAULT ; 
 int /*<<< orphan*/  TCW_TIDAW_FORMAT_DEFAULT ; 
 int /*<<< orphan*/  memset (struct tcw*,int /*<<< orphan*/ ,int) ; 

void tcw_init(struct tcw *tcw, int r, int w)
{
	memset(tcw, 0, sizeof(struct tcw));
	tcw->format = TCW_FORMAT_DEFAULT;
	tcw->flags = TCW_FLAGS_TIDAW_FORMAT(TCW_TIDAW_FORMAT_DEFAULT);
	if (r)
		tcw->r = 1;
	if (w)
		tcw->w = 1;
}