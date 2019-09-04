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
struct Layer2 {int /*<<< orphan*/ ** windowar; } ;

/* Variables and functions */
 int MAX_WINDOW ; 

__attribute__((used)) static void
InitWin(struct Layer2 *l2)
{
	int i;

	for (i = 0; i < MAX_WINDOW; i++)
		l2->windowar[i] = NULL;
}