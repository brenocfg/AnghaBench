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
struct fritzcard {int /*<<< orphan*/ * bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  modehdlc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
inithdlc(struct fritzcard *fc)
{
	modehdlc(&fc->bch[0], -1);
	modehdlc(&fc->bch[1], -1);
}