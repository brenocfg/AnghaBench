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
struct fs3270 {int /*<<< orphan*/  init; scalar_t__ active; } ;

/* Variables and functions */
 scalar_t__ raw3270_request_final (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
fs3270_working(struct fs3270 *fp)
{
	/*
	 * The fullscreen view is in working order if the view
	 * has been activated AND the initial request is finished.
	 */
	return fp->active && raw3270_request_final(fp->init);
}