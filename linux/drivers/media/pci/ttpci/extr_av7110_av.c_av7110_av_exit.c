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
struct av7110 {int /*<<< orphan*/ * ipack; } ;

/* Variables and functions */
 int /*<<< orphan*/  av7110_ipack_free (int /*<<< orphan*/ *) ; 

void av7110_av_exit(struct av7110 *av7110)
{
	av7110_ipack_free(&av7110->ipack[0]);
	av7110_ipack_free(&av7110->ipack[1]);
}